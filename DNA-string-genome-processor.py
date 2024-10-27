class Attributes:
    text = """
    Choose an option:
[1] Compute a reverse complement of a k-mer pattern
[2] Count a k-mer pattern
[3] Find most frequent k-mer patterns
[4] Exit program

Select an operation [1/2/3/4]: """

class CustomError:
    e1 = ">> Invalid text data. Expected text file: containing 'A', 'C', 'T', and 'G'"
    e2 = ">> Invalid data type. Expected input: '.txt' files "

def data_validation(inputtext:str):
    validation = ['A', 'C', 'T', 'G']
    for n in inputtext:
        if n in validation:
            pass
        else:
            return CustomError.e1
    return True

def read_file(file:str): # fix this lahh
    if file.endswith(".txt"):    
        contents = open(file, "r").readline()
        validate = data_validation(contents)
        if validate == True:
            return contents
        else:
            return print(validate)
    else:
        return print(CustomError.e2)


def reverse_pattern(pattern:str):
    patternList = {
    "A" : "T",
    "T" : "A",
    "G" : "C",
    "C" : "G"
    }
    reversedPattern = ""
    for n in pattern[::-1]:
        if n in patternList:
            reversedPattern += patternList[n]
        else:
            return False
    return reversedPattern

def count_k_mer(pattern:str, target:str, decider:bool): 
    # decider is used to find the reverse target or not TASK
    k_mer = 0
    if decider == True: # if bool == True, then it will find the reversed target too
        target_k_mer = reverse_pattern(target)
    else:
        target_k_mer = target # otherwise it will find the exact target
    for n in range(0, len(pattern) - len(target)+1):
        k_mer_search = pattern[n:len(target)+n]
        if k_mer_search == target or k_mer_search == target_k_mer:
            k_mer+=1
    return k_mer

def frequent_k_mer(pattern:str, k:int):
    genome = {}
    result_k_mer = []
    temp = 0
    for n in range(0, len(pattern)-k+1): # finding k_mer in the string
        k_mer_search = pattern[n:k+n]
        reversedTarget = reverse_pattern(k_mer_search)
        if k_mer_search in genome:
            genome[k_mer_search] += 1
        elif reversedTarget in genome:
            genome[reversedTarget] += 1
        else:
            genome[k_mer_search] = 1
    for key, value in genome.items(): # Eliminating least k_mer combinations 
        if value > temp:
            temp += value
            result_k_mer.clear()
            result_k_mer.append(key)
        elif value < temp:
            pass
        else:
            result_k_mer.append(key)
    for n in range(0, len(result_k_mer)): # TASK : making sure that the k_mer is exist in the string
        reversedTest = reverse_pattern(result_k_mer[n])
        if count_k_mer(pattern, reversedTest, False) > 0:
            result_k_mer.append(reversedTest)
    return result_k_mer # Returned with list

def mainProgram():
    while(True):
        try:
            filename = str(input("Genome file name: "))
            text = read_file(filename)
            if text[0:6] != "Invalid":
                break 
        except TypeError:
            continue
        except Exception as error:
            print(f">> {error}")
    while(True):
        decision = str(input(Attributes.text))
        if decision == "1":
            while(True):
                patterninput = str(input("Input your pattern : "))
                if data_validation(patterninput) == True:
                    break
                else: 
                    print("Wrong input, expected input = 'A', 'C', 'G', 'T'")
            result = reverse_pattern(patterninput)
            print(result)
        elif decision == "2":
            while(True):
                patterninput = str(input("Input your pattern : "))
                if data_validation(patterninput) == True:
                    break
                else: 
                    print("Wrong input, expected input = 'A', 'C', 'G', 'T'")
            result = count_k_mer(text, patterninput, True)
            print(result)
        elif decision == "3":
            while(True):
                k_value = int(input("Input your value of k: "))
                if len(text) >= k_value:
                    break
                else:
                    print(f"Input surpassed the text input, expected input: less than {len(text)}")
            result = frequent_k_mer(text, k_value)
            for n in result:
                print(n)
        elif decision == "4":
            print("Program finished")
            break
        else:
            print("Invalid input, please try again")
mainProgram()
