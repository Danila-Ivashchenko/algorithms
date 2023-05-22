import numpy as np
import matplotlib.pyplot as plt


def parse_wav_file(file_path):
    with open(file_path, "rb") as file:
        _ = file.read(12)
        _ = file.read(8)
        format = file.read(16)

        channels = format[2]
        frame_rate = int.from_bytes(format[4:8], byteorder="little")
        num_frames = int.from_bytes(format[8:12], byteorder="little")

        frames = np.frombuffer(file.read(), dtype=np.int16)

    left_channel = frames[::channels]
    right_channel = frames[1::channels]
    duration = num_frames / frame_rate
    ts = np.linspace(0, duration, len(left_channel))

    return [left_channel, right_channel, ts]


if __name__ == "__main__":
    path = "samples/sample3.wav"

    data = parse_wav_file(path)
    fig = plt.figure(figsize=(12, 6))
    fig.suptitle(f"wav audio channels", fontsize=18, fontweight="regular")

    fig.text(0.5, 0.04, "sec", ha="center", va="center", fontsize=12)
    fig.text(
        0.06,
        0.5,
        "amplitude",
        ha="center",
        va="center",
        rotation="vertical",
        fontsize=12,
    )

    ax = fig.add_subplot()
    ax.plot(
        data[2],
        data[0],
        color="#311847",
        linestyle="-",
        linewidth=1,
        label="Left Channel",
    )
    ax.plot(
        data[2],
        data[1],
        color="#E09F7D",
        linestyle="-",
        linewidth=1,
        label="Right Channel",
    )

    plt.legend()
    plt.show()
