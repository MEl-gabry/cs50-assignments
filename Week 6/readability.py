text = input("Text: ")
letter_count = 0
word_count = 1
sentence_count = 0
for letter in text:
    if letter.isalpha():
        letter_count += 1
    elif letter == " ":
        word_count += 1
    elif letter == "." or letter == "!" or letter == "?":
        sentence_count += 1
W = word_count / 100
grade = round(0.0588 * (letter_count / W) - 0.296 * (sentence_count / W) - 15.8)
if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")