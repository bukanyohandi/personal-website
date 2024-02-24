import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

# read excel
data = pd.read_excel("Classification iris.xlsx", header = None)

# denote class as a number
data[4] = data[4].replace(["Iris-setosa", "Iris-versicolor", "Iris-virginica"], [0, 1, 2])

# binary classification method
def train(arg_data, y):
    data = pd.DataFrame.copy(arg_data)
    data[4] = data[4].replace([0, 1, 2], [1 if i == y else -1 for i in range(3)])
    
    X = data.iloc[:,:-1].values
    Y = data.iloc[:,-1:].values
    
    return np.matmul(np.matmul(np.linalg.inv(np.matmul(np.transpose(X), X)), np.transpose(X)), Y)

# binary classification method
def test(arg_data, y, W, cont = False):
    data = pd.DataFrame.copy(arg_data)
    data[4] = data[4].replace([0, 1, 2], [1 if i == y else -1 for i in range(3)])
    
    X_test = data.iloc[:,:-1].values
    Y_test = np.transpose(data.iloc[:,-1:].values)[0].tolist()
    Y_prediction = [1 if sum([X_test[i][j] * W[j] for j in range(4)]) >= 0 else -1 for i in range(len(X_test))]
    
    if(cont):
        miss_classified = sum([1 if Y_test[i] == 1 and Y_prediction[i] == -1 else 0 for i in range(len(Y_test))])
        tmp_Y_prediction = [y if Y_prediction[i] == 1 else (y + 1) % 3 for i in range(len(Y_test)) if Y_test[i] == 1]
        tmp_Y_test = [y for i in range(len(Y_test)) if Y_test[i] == 1]
        return miss_classified, tmp_Y_prediction, tmp_Y_test
    else:
        miss_classified = sum([1 if Y_test[i] != Y_prediction[i] else 0 for i in range(len(Y_test))])
        tmp_Y_prediction = [y if Y_prediction[i] == 1 else (y + 1) % 3 for i in range(len(Y_test))]
        tmp_Y_test = [y if Y_test[i] == 1 else (y + 1) % 3 for i in range(len(Y_test))]
        return miss_classified, tmp_Y_prediction, tmp_Y_test

# find that one class that is linearly separable from the other 2
def find():
    arr = []
    for i in range(3):
        training_data, testing_data = train_test_split(data, test_size = 0.2)
        x, y, z = test(testing_data, i, train(training_data, i))
        arr.append(x)
        
    return np.argmin(arr)

separable_class = find()

for loop in range(10):

    # split
    training_data, testing_data = train_test_split(data, test_size = 0.2)
    training_data_2 = training_data[training_data[4] != separable_class]
    testing_data_2 = testing_data[testing_data[4] != separable_class]
    # train
    W = train(training_data, separable_class)
    W_2 = train(training_data_2, (separable_class + 1) % 3)
    
    Y_prediction = []
    Y_prediction_1 = []
    Y_prediction_2 = []
    Y_test = []
    Y_test_1 = []
    Y_test_2 = []
    
    # test using training data
    training_miss_classified = []
    training_miss_classified_1 = []
    training_miss_classified_2 = []
    training_miss_classified_1, Y_prediction_1, Y_test_1 = test(training_data, separable_class, W, True)
    training_miss_classified_2, Y_prediction_2, Y_test_2 = test(training_data_2, (separable_class + 1) % 3, W_2)
    training_miss_classified = training_miss_classified_1 + training_miss_classified_2 
    Y_prediction = np.concatenate((Y_prediction_1, Y_prediction_2))
    Y_test = np.concatenate((Y_test_1, Y_test_2))
    
    result = np.vstack((Y_prediction, Y_test)).T
    result = pd.DataFrame(result, columns = ["predicted class", "actual class"])

    result.to_excel("classification_iris_training_result_trial_" + str(loop + 1) + ".xlsx")
     
    # test using testing data
    testing_miss_classified = []
    testing_miss_classified_1 = []
    testing_miss_classified_2 = []
    testing_miss_classified_1, Y_prediction_1, Y_test_1 = test(testing_data, separable_class, W, True)
    testing_miss_classified_2, Y_prediction_2, Y_test_2 = test(testing_data_2, (separable_class + 1) % 3, W_2)
    testing_miss_classified = testing_miss_classified_1 + testing_miss_classified_2 
    Y_prediction = np.concatenate((Y_prediction_1, Y_prediction_2))
    Y_test = np.concatenate((Y_test_1, Y_test_2))
    
    result = np.vstack((Y_prediction, Y_test)).T
    result = pd.DataFrame(result, columns = ["predicted class", "actual class"])

    result.to_excel("classification_iris_testing_result_trial_" + str(loop + 1) + ".xlsx")
    
    # Classification Error Rate calculation
    print("CER for training in trial", loop + 1, "\t=", training_miss_classified / len(training_data))
    print("CER for testing in trial", loop + 1, "\t=", testing_miss_classified / len(testing_data), "\n")
