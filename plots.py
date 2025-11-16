import csv
import matplotlib.pyplot as plt

def read_csv(filename):
    Ns = []
    random_t = []
    reverse_t = []
    almost_t = []

    with open(filename, "r") as f:
        reader = csv.reader(f)
        next(reader)
        for row in reader:
            Ns.append(int(row[0]))
            random_t.append(float(row[1]))
            reverse_t.append(float(row[2]))
            almost_t.append(float(row[3]))

    return Ns, random_t, reverse_t, almost_t


Ns, pure_r, pure_rev, pure_alm = read_csv("results_pure.csv")

thresholds = [5, 10, 20, 30, 50]
hybrid = {}

for t in thresholds:
    hybrid[t] = read_csv(f"results_hybrid_thr{t}.csv")


def plot_category(category: str, pure_arr, get_hybrid, pngname):
    plt.figure(figsize=(12, 6))
    plt.plot(Ns, pure_arr, label="Pure MergeSort", linewidth=2)
    for t in thresholds:
        plt.plot(Ns, get_hybrid(t), label=f"Hybrid T={t}", alpha=0.8)

    plt.xlabel("N")
    plt.ylabel("Time (µs)")
    plt.title(category)
    plt.grid()
    plt.legend()

    plt.savefig(pngname, dpi=200)
    plt.close()


plot_category(
    "Random — Merge vs Hybrid",
    pure_r,
    lambda t: hybrid[t][1],
    "plot_random.png"
)

plot_category(
    "Reverse — Merge vs Hybrid",
    pure_rev,
    lambda t: hybrid[t][2],
    "plot_reverse.png"
)


plot_category(
    "Almost sorted — Merge vs Hybrid",
    pure_alm,
    lambda t: hybrid[t][3],
    "plot_almost.png"
)

print("Графики сохранены: plot_random.png, plot_reverse.png, plot_almost.png")
