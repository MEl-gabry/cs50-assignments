import sys
import csv
def main():
    if len(sys.argv) != 3:
        print("Format: python dna.py CSVFILENAME TEXTFILE")
        return
    file1 = sys.argv[1]
    file2 = sys.argv[2]
    csv_data = []
    strs = []
    str_dict = {}
    dna_sequence = ""
    with open(file1, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            for x in range (1, len(row)):
                strs.append(row[x])
            break
        dict_reader = csv.DictReader(file)
        file.seek(0, 0)
        for row in dict_reader:
            csv_data.append(row)
    with open(file2, "r") as file:
        dna_sequence = file.read()
    for str in strs:
        i = 0
        j = len(str)
        greatest_conseq_strs = 0
        conseq_strs = 0
        found = False
        while j <= len(dna_sequence):
            if str in dna_sequence[i:j]:
                conseq_strs += 1
                found = True
            else:
                conseq_strs = 0
                found = False
            if conseq_strs > greatest_conseq_strs:
                greatest_conseq_strs = conseq_strs
            if found == True:
                i += len(str)
                j += len(str)
            else:
                i += 1
                j += 1
        str_dict.update({str : greatest_conseq_strs})
    for person in csv_data:
        matches = 0
        for str in person.items():
            if str[0] == "name":
                continue
            elif str_dict[str[0]] == int(str[1]):
                matches += 1
        if matches == len(str_dict):
            print(person["name"])
            return
    print("No Match")
        
if __name__ == "__main__":
    main()