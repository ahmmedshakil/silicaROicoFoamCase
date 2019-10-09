from numpy import loadtxt
import matplotlib.pyplot as plt
import os

membraneSegmentArea = 5.919633e-05
info = loadtxt("postProcessing/flowRatePatch(name=membrane)/0/surfaceFieldValue.dat")

initialisationTime = 0.45


time = info[:, 0] / 3600
flowRate = info[:, 1]
flux = flowRate / membraneSegmentArea * 3600 * 1000  # [L/m2.h]

#take the last value of each group of time steps (the quasi SS value)
fwdDeltaT = [0] + [time[i+1]-time[i] for i in range(len(time)-1)]
time_qs = []
flux_qs = []
flag = True
for t, f, d in zip(time, flux, fwdDeltaT):
	if d>1/3600:
		time_qs.append(t)
		flux_qs.append(f)
		flag = False
	elif flag == True:
		time_qs.append(t)
		flux_qs.append(f)		


plt.scatter(time_qs, flux_qs, color="k")

plt.xlabel(r"Time ${\rm \,(ms)}$")  # (r"Time ${\rm \,(h)}$")
plt.ylabel(r"Membrane Flux ${\rm \,(L/m^2.h)}$")
plt.minorticks_on()
plt.show()

# dirFile = "/home/riley/Documents/Thesis/FinalReport/results/figures/"
# plt.savefig(os.path.join(dirFile, "fluxDecline.pdf"))  # , dpi=300)

