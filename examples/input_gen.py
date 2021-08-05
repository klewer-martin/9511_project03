from string import digits
from time import strftime, gmtime
from random import randint, choice

LINES = 1000000

# OUTPUT:
#     ID_TRANSACCION, ID_USUARIO, FECHA, MONTO, NUMERO DE TRAJETA, DESCRIPCION
#     123412,1,05/11/2011 10:00:00,-10,4916288217067475, Compra supermercado

descs = [ "Compras supermercado", "Pago tarjeta", "Compras libreria", "Pago Mecanico", "Pago Dentista", "Pago Servicios online", "Compras Ferreteria",  "Compras Accesorios Informatica", "Compras farmacia", "Ventas online", "Extraccion cajero" ]

def calculate_luhn(cc):
    num = list(map(int, str(cc)))
    check_digit = 10 - sum(num[-2::-2] + [sum(divmod(d * 2, 10)) for d in num[::-2]]) % 10
    return 0 if check_digit == 10 else check_digit

def generate_card(type):
    """
    Prefill some values based on the card type
    """
    card_types = ["americanexpress","visa13", "visa16","mastercard","discover"]

    def prefill(t):
        # typical number of digits in credit card
        def_length = 16

        """
        Prefill with initial numbers and return it including the total number of digits
        remaining to fill
        """
        if t == card_types[0]:
            # american express starts with 3 and is 15 digits long
            # override the def lengths
            return [3, randint(4,7)], 13

        elif t == card_types[1] or t == card_types[2]:
            # visa starts with 4
            if t.endswith("16"):
                return [4], def_length - 1
            else:
                return [4], 12

        elif t == card_types[3]:
            # master card start with 5 and is 16 digits long
            return [5, randint(1,5)], def_length - 2

        elif t == card_types[4]:
            # discover card starts with 6011 and is 16 digits long
            return [6, 0, 1, 1], def_length - 4

        else:
            # this section probably not even needed here
            return [], def_length

    def finalize(nums):
        """
        Make the current generated list pass the Luhn check by checking and adding
        the last digit appropriately bia calculating the check sum
        """
        check_sum = 0

        #is_even = True if (len(nums) + 1 % 2) == 0 else False

        """
        Reason for this check offset is to figure out whether the final list is going
        to be even or odd which will affect calculating the check_sum.
        This is mainly also to avoid reversing the list back and forth which is specified
        on the Luhn algorithm.
        """
        check_offset = (len(nums) + 1) % 2

        for i, n in enumerate(nums):
            if (i + check_offset) % 2 == 0:
                n_ = n*2
                check_sum += n_ -9 if n_ > 9 else n_
            else:
                check_sum += n
        return nums + [10 - (check_sum % 10) ]

    # main body
    t = type.lower()
    if t not in card_types:
        print("Unknown type: '%s'" % type)
        print("Please pick one of these supported types: %s" % card_types)
        return

    initial, rem = prefill(t)
    so_far = initial + [randint(1,9) for x in range(rem - 1)]
    return ("".join(map(str,finalize(so_far))))

def generate_file(max_lines):
    id_transaction_base = 123400
    id_user_base = 1
    id_user_max = 50000
    amount_base = 1
    amount_max = 10000
    for i in range(max_lines):
        id_transaction = (i + id_transaction_base)
        id_user = randint(id_user_base, id_user_max)

        card_nr = generate_card("visa16")
        while calculate_luhn(card_nr) != 0:
            card_nr = generate_card("visa16")

        date = strftime("%d.%m.%Y %H:%M:%S", gmtime(1320487200 + i))
        
        j = randint(1, len(descs) - 1)
        desc = descs[j] 

        if j > 8:   amount = randint(amount_base, amount_max)
        else:   amount = randint(-amount_max, -amount_base)

        print(id_transaction,id_user,date,amount,card_nr,desc, sep=',')

generate_file(LINES)
