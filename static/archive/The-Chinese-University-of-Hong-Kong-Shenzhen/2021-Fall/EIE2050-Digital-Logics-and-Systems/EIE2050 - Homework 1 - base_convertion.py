# Yohandi (120040025)
# EIE2050 - Assignment 1

# Note:
# > The parameter value is allowed for both integer type and string type
# + Integer type for parameter only works if the value's digits consist
#   of 0..9 (without leading zeros)
# + String type for parameter works for every value as long as it is
#   constrained with its respective base
# + Example:
#   hexadecimal_to_decimal(A9) is a FAILED function call
#   hexadecimal_to_decimal("A9") is a SUCCESS function call
#   binary_to_octal(10101) is a SUCCESS function call
#   binary_to_octal("10101") is also a SUCCESS function call
#
# > The value only works within 0..255 (base 10) as required in the problem
#
# > An error value input results in "None" output

def reverse_dictionary(old_dictionary):
    new_dictionary = {}
    for key, value in old_dictionary.items():
        new_dictionary[value] = key
    return new_dictionary

def valid_binary(value):
    base_number = ["0", "1"]
    if len(value) <= 8 and sorted(list(set([value[i] for i in range(len(value))] + base_number))) == base_number:
        return True
    else:
        return False

def valid_octal(value):
    base_number = ["0", "1", "2", "3", "4", "5", "6", "7"]
    if len(value) <= 3 and sorted(list(set([value[i] for i in range(len(value))] + base_number))) == base_number and not(len(value) == 3 and value[0] in ["4", "5", "6", "7"]):
        return True
    else:
        return False

def valid_decimal(value):
    base_number = ["0", "1", "2", "3", "4", "5", "6", "7",
                   "8", "9"]
    if sorted(list(set([value[i] for i in range(len(value))] + base_number))) == base_number and int(value) < 256:
        return True
    else:
        return False

def valid_hexadecimal(value):
    base_number = ["0", "1", "2", "3", "4", "5", "6", "7",
                   "8", "9", "A", "B", "C", "D", "E", "F"]
    if len(value) <= 2 and sorted(list(set([value[i] for i in range(len(value))] + base_number))) == base_number:
        return True
    else:
        return False
    
def binary_to_octal(value, reverse = False):
    if value == None:
        return None
    value = str(value)

    base_number = {"000": "0", "001": "1", "010": "2", "011": "3",
                   "100": "4", "101": "5", "110": "6", "111": "7"}
    
    if reverse == False:
        if not(valid_binary(value)):
            return None
        value = "0" * (3 - (len(value) % 3)) + value
        value = "".join([base_number[value[i: i + 3]] for i in range(0, len(value), 3)])
    else:
        if not(valid_octal(value)):
            return None
        base_number = reverse_dictionary(base_number)
        value = "".join([base_number[value[i]] for i in range(len(value))])
    
    return value.lstrip("0")

def binary_to_decimal(value, reverse = False):
    if value == None:
        return None
    value = str(value)

    power_of_two = [1, 2, 4, 8, 16, 32, 64, 128]

    if reverse == False:
        if not(valid_binary(value)):
            return None
        value = "0" * (8 - len(value)) + value
        value = str(sum([power_of_two[7 - i] for i in range(8) if value[i] == "1"]))
    else:
        if not(valid_decimal(value)):
            return None
        int_value = int(value)
        value = ""
        for i in range(7, -1, -1):
            if int_value >= power_of_two[i]:
                value += "1"
                int_value -= power_of_two[i]
            else:
                value += "0"

    return value.lstrip("0")
    
def binary_to_hexadecimal(value, reverse = False):
    if value == None:
        return None
    value = str(value)
    
    base_number = {"0000": "0", "0001": "1", "0010": "2", "0011": "3",
                   "0100": "4", "0101": "5", "0110": "6", "0111": "7",
                   "1000": "8", "1001": "9", "1010": "A", "1011": "B",
                   "1100": "C", "1101": "D", "1110": "E", "1111": "F"}

    if reverse == False:
        if not(valid_binary(value)):
            return None
        value = "0" * (4 - (len(value) % 4)) + value
        value = "".join([base_number[value[i: i + 4]] for i in range(0, len(value), 4)])
    else:
        if not(valid_hexadecimal(value)):
            return None
        base_number = reverse_dictionary(base_number)
        value = "".join([base_number[value[i]] for i in range(len(value))])
    
    return value.lstrip("0")
    
def octal_to_binary(value):
    return binary_to_octal(value, True)

def octal_to_decimal(value):
    return binary_to_decimal(octal_to_binary(value))

def octal_to_hexadecimal(value):
    return binary_to_hexadecimal(octal_to_binary(value))

def decimal_to_binary(value):
    return binary_to_decimal(value, True)

def decimal_to_octal(value):
    return binary_to_octal(decimal_to_binary(value))

def decimal_to_hexadecimal(value):
    return binary_to_hexadecimal(decimal_to_binary(value))

def hexadecimal_to_binary(value):
    return binary_to_hexadecimal(value, True)

def hexadecimal_to_octal(value):
    return binary_to_octal(hexadecimal_to_binary(value))

def hexadecimal_to_decimal(value):
    return binary_to_decimal(hexadecimal_to_binary(value))

base_list = ["binary", "octal", "decimal", "hexadecimal"]
conversion_from = input("Convert from [binary/octal/decimal/hexadecimal]: ")
while conversion_from not in base_list:
    print("ERROR: Base does not exist.")
    conversion_from = input("Convert from [binary/octal/decimal/hexadecimal]: ")

value = input("Input your " + conversion_from + " value: ")
while eval("valid_" + conversion_from + "(value)") == False:
    print("ERROR: Input value is invalid")
    value = input("Input your " + conversion_from + " value: ")
    
base_list.remove(conversion_from)
base_list.append("all")
conversion_to = input("Convert " + value + " to [" + "/".join(base_list) + "]: ")
while conversion_to not in base_list:
    print("ERROR: Base does not exist.")
    conversion_to = input("Convert " + value + " to [" + "/".join(base_list) + "]: ")
base_list.remove("all")

if conversion_to == "all":
    print(value + " in " + conversion_from + " is ", end = "")
    for i in range(len(base_list)):
        if i == len(base_list) - 1:
            print(", and ", end = "")
        elif i != 0:
            print(", ", end = "")
        print(eval(conversion_from + "_to_" + base_list[i] + "(value)") + " in " + base_list[i], end = "")
    print(".")
else:
    print(value + " in " + conversion_from + " is " + eval(conversion_from + "_to_" + conversion_to + "(value)") + " in " + conversion_to + ".")
    
