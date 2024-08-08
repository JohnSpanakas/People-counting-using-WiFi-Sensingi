 
import json

file1 = 'C:/Users/User/Desktop/DATA/ZB107 TEST/ground truth/ZB107_test_ground_truth.json'
file2 = 'C:/Users/User/Desktop/DATA/ZB107 TEST/merged_ZB107_TEST_inference_data.json'
file3 = 'C:/Users/User/Desktop/DATA/ZB107 TEST/labeled_ZB107_TEST_data.json'
#ΑΡΧΙΚΟΠΟΙΗΣΗ ΠΙΝΑΚΩΝ
Time = {}
datetime = {}
Num_of_People = {}

with open(file1, 'r') as f1, open(file2, 'r') as f2:
    #ΜΕΤΑΤΡΟΠΗ ΑΡΧΕΙΩΝ string ΣΕ json object
    input_string1 = f1.read()
    ground_truth_data = json.loads(input_string1)
    input_string2 = f2.read()
    csi_data = json.loads(input_string2)
    ground_truth_data = sorted(ground_truth_data, key=lambda x: x["Time"])
    csi_data = sorted(csi_data, key=lambda x: x["datetime"])
    
#ΑΠΟΘΗΚΕΥΣΗ timestamps ΣΕ ΠΙΝΑΚΕΣ
for i in range(len(ground_truth_data)):
    if "Time" in ground_truth_data[i]:
        value = ground_truth_data[i]["Time"]
        Time[i] = value
    if "Number of People" in ground_truth_data[i]:
        cnt = ground_truth_data[i]["Number of People"]
        Num_of_People[i] = cnt
        
for i in range(len(csi_data)):
    if "datetime" in csi_data[i]:
        value = csi_data[i]["datetime"]
        datetime[i] = int(float(value))

#ΣΥΓΚΡΙΣΗ ΚΑΙ ΤΙΤΛΟΦΟΡΗΣΗ
i=0
j=0
for line in csi_data:
    if Time[i] >= datetime[j]:
        line["class"] = Num_of_People[i]
        j=j+1
    else:
        if i > ((len(ground_truth_data)-1)):
            break
        elif i== ((len(ground_truth_data)-1)):
            line["class"] = Num_of_People[i]
            j=j+1
        else:
            line["class"] = Num_of_People[i]
            i=i+1
            
                

with open(file3, 'w') as f:
    json.dump(csi_data, f)

# Convert the merged JSON list to a string with new lines
output_str = ',\n'.join(json.dumps(item) for item in csi_data)

# Write the output to a new file
with open(file3, "w") as f:
    f.write('[')
    f.write(output_str)
    f.write(']')

