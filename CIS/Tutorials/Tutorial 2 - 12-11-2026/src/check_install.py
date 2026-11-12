"""Run:  python check_install.py   -> checks OpenMM, numpy, matplotlib, NAMD."""
import os, shutil, sys
os.chdir(os.path.dirname(os.path.abspath(__file__)))   # works from any folder
ok = True
try:
    import openmm as mm
    print("OpenMM", mm.__version__, "| platforms:", [mm.Platform.getPlatform(i).getName() for i in range(mm.Platform.getNumPlatforms())])
    from openmm import app, unit
    prm = app.AmberPrmtopFile('inputs/trpcage_wat.prmtop')
    s = prm.createSystem(nonbondedMethod=app.PME, constraints=app.HBonds)
    print("OpenMM built the Trp-cage system:", s.getNumParticles(), "atoms")
except Exception as e:
    ok = False; print("OpenMM FAILED:", e)
for m in ("numpy", "matplotlib"):
    try: __import__(m); print(m, "ok")
    except Exception as e: ok = False; print(m, "MISSING")
namd = shutil.which("namd3") or shutil.which("namd2")
if namd:
    print("NAMD found:", namd)
else:
    ok = False; print("NAMD not on PATH (namd3 / namd2)")
print("\nALL GOOD" if ok else "\nSOMETHING IS MISSING - see above, and 1_BEFORE_CLASS_Install.pdf")
