# 11) id не делится нацело на 5, логин — палиндром, в пароле есть хотя бы одна нечётная цифра и одна заглавная буква,
import random as rnd
from string import ascii_lowercase
from string import ascii_uppercase
import pprint


def random_id():
    return rnd.randint(1000, 9999) * 10 + rnd.choice([1, 2, 3, 4, 6, 7, 8, 9])


def random_login():
    s = rnd.choices(ascii_lowercase, k=3)
    return "".join(s + s[::-1])


def random_password():
    odd_digit = ["1", "3", "5", "7", "9"]

    random_char = rnd.choice(ascii_uppercase)
    random_odd_digit = rnd.choice(odd_digit)

    sequence = odd_digit + ["0", "2", "4", "6", "8"] + list(ascii_uppercase) + list(ascii_lowercase)

    random_sequence = rnd.choices(sequence, k=8)
    random_sequence += random_char + random_odd_digit

    rnd.shuffle(random_sequence)
    return "".join(random_sequence)


def generate_all(n):
    id = set()
    login = set()
    password = set()

    while len(id) < n:
        id.add(random_id())
    while len(login) < n:
        login.add(random_login())
    while len(password) < n:
        password.add(random_password())

    return list(zip(id, login, password))


n = int(input())
data = generate_all(n)

pp = pprint.PrettyPrinter()
pp.pprint(data)
