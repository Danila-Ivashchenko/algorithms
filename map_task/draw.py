from matplotlib import pyplot as plt

n = []

cpp_data = [[], []]

py_data = [[], []]


with open("data/map_cpp_stat.txt", "r") as file:
    for line in file:
        elements = list(map(int, line.split()))
        n += [elements[0]]
        cpp_data[0] += [elements[1]]
        cpp_data[1] += [elements[2]]


with open("data/map_py_stat.txt", "r") as file:
    for line in file:
        elements = list(map(int, line.split()))
        py_data[0] += [elements[1]]
        py_data[1] += [elements[2]]

ax = plt.subplot(1, 2, 1)
plt.title("dependence of weight on elements count")
plt.xlabel("Elements count")
plt.ylabel("Bytes")
plt.plot(n, cpp_data[0], label="C++")
plt.plot(n, py_data[0], label="Python")
ax.set_xscale("log")
ax.set_yscale("log")
plt.grid()
plt.legend()

ax = plt.subplot(1, 2, 2)
plt.title("dependence of time on elements count")
plt.xlabel("Elements count")
plt.ylabel("milliseconds")
plt.plot(n, cpp_data[1], label="C++")
plt.plot(n, py_data[1], label="Python")
ax.set_xscale("log")
ax.set_yscale("log")
plt.grid()
plt.legend()

plt.show()