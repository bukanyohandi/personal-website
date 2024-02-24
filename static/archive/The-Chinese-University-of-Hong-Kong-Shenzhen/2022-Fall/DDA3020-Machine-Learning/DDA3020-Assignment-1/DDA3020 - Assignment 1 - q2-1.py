import math
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split

# read csv
data = pd.read_csv("Regression.csv")

# delete two attributes (station and date) and drop each row that has NaN value
data = data.drop(["station", "Date"], axis = 1).dropna()

for loop in range(10):

    # split
    training_data, testing_data = train_test_split(data, test_size = 0.2)

    # train (W = (X^T X)^-1 X^T Y)
    X = training_data.iloc[:,:-2].values
    Y = training_data.iloc[:,-2:].values
    W = np.matmul(np.matmul(np.linalg.inv(np.matmul(np.transpose(X), X)), np.transpose(X)), Y)

    # test using testing data (f_w,b(X_test) = X_test W)
    X_test = testing_data.iloc[:,:-2].values
    Y_prediction = np.matmul(X_test, W)
    Y_test = testing_data.iloc[:,-2:].values

    result = np.concatenate((Y_prediction, Y_test), axis = 1)
    result = pd.DataFrame(result, columns = ["predicted next-day maximum temperature", "predicted next-day minimum temperature", "actual next-day maximum temperature", "actual next-day minimum temperature"])

    result.to_excel("regression_result_trial_" + str(loop + 1) + ".xlsx")
    
    # RMSE calculation
    RMSE = math.sqrt(np.square(np.subtract(Y_test, Y_prediction)).mean())
    
    print("RMES in trial", loop + 1, "\t=", RMSE)