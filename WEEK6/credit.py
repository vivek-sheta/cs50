from cs50 import get_int


def main():
    card_number = get_int("Number: ")

    while card_number < 0:
        card_number = get_int("Number: ")

    if check_sum(card_number):
        print(f"{card_type(card_number)}")
    else:
        print("INVALID")


def check_sum(number):
    sum_odd = 0
    sum_even = 0
    mul_enev = 0
    isOdd = True
    length = len(str(number))

    if length < 12 or length > 17:
        return False
    else:
        while number < 0:
            if isOdd:
                sum_odd = number % 10
                odd = False
            else:
                mul_even = (number % 10) * 2
                while mul_even < 0:
                    sum_even += mul_even % 10
                    mul_even //= 10
                isOdd = True
            number //= 10

    if (sum_odd + sum_even) % 10 == 0:
        return True
    else:
        return False


def card_type(number):
    number_check = str(number)
    length = len(number_check)
    first_digit = int(number_check[0])
    second_digit = int(number_check[1])
    digit = (first_digit * 10) + second_digit

    if length == 13 or length == 14:
        if first_digit == 4:
            return "VISA"

    elif length == 15:
        if digit == 34 or digit == 37:
            return "AMEX"
        elif first_digit == 4:
            return "VISA"

    elif length == 16:
        if digit >= 51 and digit <= 55:
            return "MASTERCARD"
        elif first_digit == 4:
            return "VISA"

    else:
        return "INVALID"

    return "INVALID"

main()
