import pandas as pd
import matplotlib.pyplot as plt
import glob
import os
import math


data_dir = "./simulationData/tracking/trackingSet1/"  #expected to be run from Neural_Net dir.
pattern = os.path.join(data_dir, "*.csv")


plt.figure(figsize=(10, 6))


for file in sorted(glob.glob(pattern)):
   
    angle = os.path.splitext(os.path.basename(file))[0]
    

   
    df = pd.read_csv(file)
    
    
    plt.plot(df.iloc[:, 0], df.iloc[:, 1], label=f"{float(angle)}°")

# --- STYLE ---
plt.xlabel("x")
plt.ylabel("y")
plt.title("Projectile Trajectories for Different Angles, 10 m/s headwind")
plt.legend(title="Angle", bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True)
plt.tight_layout()
plt.savefig("figures/testTrajectories.png")
plt.show()
