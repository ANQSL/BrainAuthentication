import sys

sys.path.append("D:\\project\\BrainAuthentication\\Calculate\\identity_recognition")
from calculate import Calculate
from communicate import Communication

if __name__ == "__main__":
    communicate = Communication(32, 1000)
    calculate = Calculate()
    communicate.start()
    calculate.start()
    print("计算启动")
    # while (True):
    #     pass
