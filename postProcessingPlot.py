from numpy import loadtxt
import matplotlib.pyplot as plt
import os

membraneSegmentArea = 5.919633e-05
initialisationTime = 0.45


def downSample(xs, ys):
    """take the last value of each group of time steps (the quasi SS value)
    """
    fwdDeltaY = [0] + [xs[i + 1] - xs[i] for i in range(len(xs) - 1)]
    x_qs = []
    y_qs = []

    flag = True

    for x, y, d in zip(xs, ys, fwdDeltaY):
        if d > 1 / 3600:
            x_qs.append(x)
            y_qs.append(y)
            flag = False
        elif flag == True:
            x_qs.append(x)
            y_qs.append(y)
    return x_qs, y_qs


# Flux decline
info = loadtxt("postProcessing/flowRatePatch(name=membrane)/0/surfaceFieldValue.dat")
time = info[:, 0] / 3600
flowRate = info[:, 1]
flux = flowRate / membraneSegmentArea * 3600 * 1000  # [L/m2.h]
time_qs, flux_qs = downSample(time, flux)

plt.scatter(time_qs, flux_qs, color="k")
plt.xlabel(r"Time ${\rm \,(ms)}$")  # (r"Time ${\rm \,(h)}$")
plt.ylabel(r"Membrane Flux ${\rm \,(L/m^2.h)}$")
plt.minorticks_on()
plt.show()

# dirFile = "/home/riley/Documents/Thesis/FinalReport/results/figures/"
# plt.savefig(os.path.join(dirFile, "fluxDecline.pdf"))  # , dpi=300)


# Silica Deposit
info = loadtxt("postProcessing/silicaDepositMass/0/surfaceFieldValue.dat")
time = info[:, 0] / 3600
membraneSilicaMass = info[:, 1] / membraneSegmentArea * 1000  # [mg/m2]
time_qs, membraneSilicaMass_qs = downSample(time, membraneSilicaMass)

plt.scatter(time_qs, membraneSilicaMass_qs, color="k")
plt.xlabel(r"Time ${\rm \,(ms)}$")  # (r"Time ${\rm \,(h)}$")
plt.ylabel(r"Mass of silica on membrane ${\rm \,(mg/m^2)}$")
plt.minorticks_on()
plt.show()

