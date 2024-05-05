from calculate import Calculate
from communicate import Communication

if __name__ == "__main__":

    communicate = Communication(32, 250)
    calculate = Calculate()
    communicate.start()
    calculate.start()
    print("计算启动")
    # while (True):
    #     pass
