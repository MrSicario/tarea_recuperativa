import json, matplotlib.pyplot as plt, matplotlib.patches as mpatches

# Script to generate graphs for report.

with open('data.json', 'r') as file:
    json_data = json.load(file)

fig, ax = plt.subplots()
# Using logarithmic scale to compensate given exponential growth of x axis.
ax.plot(json_data["exp1"]["n"], json_data["exp1"]["time"], 'D--', color="#037971")
ax.set(xlabel="|S|", xscale="log",
       ylabel="time [s]", yscale="log",
       title="Array size Vs Construction time")
ax.grid(alpha=0.5)
fig.savefig("figures/linear_time.png")
ax.cla()

ax.plot(json_data["exp1"]["n"], json_data["exp1"]["size"], 'D--', color="#037971")
ax.set(xlabel="|S|", xscale="log",
       ylabel="|Hash table|", yscale="log",
       title="Array size Vs Hash table size")
ax.grid(alpha=0.5)
fig.savefig("figures/linear_size.png")
ax.cla()

time_mean = sum(json_data["exp2"]["time"][1:])/len(json_data["exp2"]["time"][1:])

ax.plot(json_data["exp2"]["k"][1:], json_data["exp2"]["time"][1:], 'D--', color="#037971")
ax.axhline(time_mean, alpha=0.5)
ax.set(xlabel="k",
       ylabel="time [s]",
       title="Constant 'k' Vs Construction time")
ax.grid(alpha=0.5)
fig.savefig("figures/k_time.png")
ax.cla()

size_mean = sum(json_data["exp2"]["size"][1:])/len(json_data["exp2"]["size"][1:])

ax.plot(json_data["exp2"]["k"][1:], json_data["exp2"]["size"][1:], 'D--', color="#037971")
ax.axhline(size_mean, alpha=0.5)
ax.set(xlabel="k",
       ylabel="|Hash table|",
       title="Constant 'k' Vs Hash table size")
ax.grid(alpha=0.5)
fig.savefig("figures/k_size.png")
ax.cla()

ax.plot(json_data["exp3"]["c"][:2], json_data["exp3"]["time"][:2], 'D--', color="#037971")
ax.set(xlabel="c",
       ylabel="|Hash table|",
       title="Constant 'c' Vs Construction time")
ax.grid(alpha=0.5)
fig.savefig("figures/c_time.png")
ax.cla()

ax.plot(json_data["exp3"]["c"][:2], json_data["exp3"]["size"][:2], 'D--', color="#037971")
ax.set(xlabel="c",
       ylabel="|Hash table|",
       title="Constant 'c' Vs Hash table size")
ax.grid(alpha=0.5)
fig.savefig("figures/c_size.png")
ax.cla()

def color_picker(n : int):
    match n:
        case 1:
            return "#037971"
        case 2:
            return "#FDE74C"
        case 3:
            return "#9BC53D"
        case 4:
            return "#E55934"
        case 5:
            return "#FA7921"
        case 6:
            return "#4B3F72"
        case 7:
            return "#8E3B46"
        case 8:
            return "#FFCAE9"
        case _:
            return "#011638"

patch_1 =  mpatches.Patch(color="#037971", label='c=1', alpha=0.5)
patch_2 =  mpatches.Patch(color="#FDE74C", label='c=2', alpha=0.5)
patch_3 =  mpatches.Patch(color="#9BC53D", label='c=3', alpha=0.5)
patch_4 =  mpatches.Patch(color="#E55934", label='c=4', alpha=0.5)

ax.scatter(json_data["exp4"][0]["size"], json_data["exp4"][0]["time"], s=[5], c=[color_picker(x) for x in json_data["exp4"][0]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][1]["size"], json_data["exp4"][1]["time"], s=[5*2**2]*2, c=[color_picker(x) for x in json_data["exp4"][1]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][2]["size"], json_data["exp4"][2]["time"], s=[5*3**2]*3, c=[color_picker(x) for x in json_data["exp4"][2]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][3]["size"], json_data["exp4"][3]["time"], s=[5*4**2]*4, c=[color_picker(x) for x in json_data["exp4"][3]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][4]["size"], json_data["exp4"][4]["time"], s=[5*5**2]*5, c=[color_picker(x) for x in json_data["exp4"][4]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][5]["size"], json_data["exp4"][5]["time"], s=[5*6**2]*6, c=[color_picker(x) for x in json_data["exp4"][5]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][6]["size"], json_data["exp4"][6]["time"], s=[5*7**2]*7, c=[color_picker(x) for x in json_data["exp4"][6]["c"]], alpha=0.5)
ax.scatter(json_data["exp4"][7]["size"], json_data["exp4"][7]["time"], s=[5*8**2]*8, c=[color_picker(x) for x in json_data["exp4"][7]["c"]], alpha=0.5)
ax.legend(handles=[patch_1, patch_2, patch_3, patch_4])
ax.set(xlabel="Size of Hash table",
       ylabel="Time [s]",
       title="Scatter graph of 'k' & 'c'")
ax.grid(alpha=0.5)
fig.savefig("figures/scatter.png")