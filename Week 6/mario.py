def main():
    height = 0
    while height < 1 or height > 8:
        height = int(input("Height: "))
    pyramid(height, 0)
def pyramid(height, space):
    if height == 0:
        return
    pyramid(height - 1, space + 1)
    print(" " * space, end="")
    print("#" * height, end="")
    print("  ", end="")
    print("#" * height)
if __name__ == "__main__":
    main()