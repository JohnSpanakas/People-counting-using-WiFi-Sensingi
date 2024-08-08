import json
import os
import fileinput
# Δημιουργία κενής λίστας για να αποθηκεύτουν τα δεδομένα
merged_data = []

# Καθορισμός του φακέλου που περιέχει τα JSON αρχεία
folder_path = "C:/Users/User/Desktop/DATA/ZB107 TEST/csi data"

# Επανάληψη μέσα από τα αρχεία στο φάκελο
for filename in os.listdir(folder_path):
    if filename.endswith('.json'):
        with open(os.path.join(folder_path, filename), 'r') as file:
            json_data = json.load(file)
            merged_data.extend(json_data)
        
# Αποθήκευση του ενοποιημένου JSON αρχείου
output_file = 'C:/Users/User/Desktop/DATA/ZB107 TEST/merged_ZB107_TEST_inference_data.json'
with open(output_file, 'w') as file:
    json.dump(merged_data, file)

# Convert the merged JSON list to a string with new lines
output_str = ',\n'.join(json.dumps(item) for item in merged_data)

# Write the output to a new file
with open('C:/Users/User/Desktop/DATA/ZB107 TEST/merged_ZB107_TEST_inference_data.json', "w") as f:
    f.write('[')
    f.write(output_str)
    f.write(']')


