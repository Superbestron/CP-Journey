from datetime import datetime

cashflows = []
dates = []


def xirr():
    def xirr_equation(rate):
        return sum(c / (1 + rate) ** ((date - dates[0]).days / 365.0) for c, date in zip(cashflows, dates))

    rate = 0.1
    xirr_value = 1e9

    while abs(xirr_value) >= 1e-6:
        xirr_value = xirr_equation(rate)
        xirr_derivative = sum(
            -c * ((date - dates[0]).days / 365.0) / (1 + rate) ** (((date - dates[0]).days / 365.0) + 1)
            for c, date in zip(cashflows, dates))

        rate -= xirr_value / xirr_derivative

    return rate


N = int(input())
for i in range(N):
    flow, date = input().split()
    flow = int(flow)
    cashflows.append(flow)
    dates.append(date)

dates = [datetime.strptime(date, '%d-%b-%Y') for date in dates]

result_xirr = xirr() * 100
print(f"{result_xirr:.2f}")
