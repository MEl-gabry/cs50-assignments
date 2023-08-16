import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

danger_sql = [';', '--', "'"]

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total = cash
    for stock in stocks:
        cur_value = lookup(stock["symbol"])["price"]
        if stock["price"] != cur_value:
            stock["price"] = cur_value
        total += stock["price"]

    return render_template("index.html", stocks=stocks, total=usd(total), cash=usd(cash))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
        quote = lookup(request.form.get("symbol"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("enter a valid integer", 403)
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        elif not quote:
            return apology("enter correct symbol", 403)

        elif not request.form.get("shares"):
            return apology("must provide share number", 403)

        amount = quote["price"] * shares

        if amount > cash:
            return apology("not enough cash", 403)

        db.execute("INSERT INTO history VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], quote["symbol"], quote["name"], quote["price"], shares, datetime.now())

        cash = cash - amount

        for stock in stocks:
            if quote["name"] == stock["name"]:
                new_stock = stock["shares"] + shares
                db.execute("UPDATE stocks SET shares = ? WHERE user_id = ?", new_stock, session["user_id"])
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
                return redirect("/")

        db.execute("INSERT INTO stocks VALUES (?, ?, ?, ?, ?)", session["user_id"], quote["symbol"], quote["name"], quote["price"], shares)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", stocks=stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide a quote", 403)
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("enter a valid symbol", 403)
        value = quote["price"]
        symbol = quote["symbol"]
        name = quote["name"]
        return render_template("quoted.html", name=name, symbol=symbol, value=value)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif any(char in request.form.get("username") for char in danger_sql) or any(char in request.form.get("password") for char in danger_sql) or any(char in request.form.get("password_again") for char in danger_sql):
            return apology("nice try", 403)

        elif len(db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username"))) != 0:
            return apology("enter a unique username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("password") == request.form.get("password_again"):
            return apology("passwords must match", 403)


        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        session["user_id"] = id

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = ?", session["user_id"])
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("enter a symbol", 403)

        elif not request.form.get("shares"):
            return apology("enter shares", 403)

        quote = lookup(request.form.get("symbol"))
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("enter a valid integer", 403)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        for stock in stocks:
            if stock["symbol"] == quote["symbol"]:
                if stock["shares"] - shares < 0:
                    return apology("you don't have enough shares of this stock", 403)
                stock["shares"] -= shares
                cash += stock["price"]
                if stock["shares"] <= 0:
                    db.execute("DELETE FROM stocks WHERE symbol = ?", stock["symbol"])
                db.execute("UPDATE users SET cash = ?", cash)
                break

        db.execute("INSERT INTO history VALUES (?, ?, ?, ?, ?, ?)", session["user_id"], quote["symbol"], quote["name"], quote["price"], -shares, datetime.now())

        return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)

@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    if request.method == "POST":
        old_password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])[0]["hash"]
        if not request.form.get("old_password"):
            return apology("enter current password", 403)

        elif not request.form.get("new_password"):
            return apology("enter new password", 403)

        elif not check_password_hash(old_password, request.form.get("old_password")):
            return apology("enter correct password", 403)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("new_password")), session["user_id"])

        return render_template("password.html", changed=True)
    else:
        return render_template("password.html")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
