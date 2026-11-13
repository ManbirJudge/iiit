import os
import shutil

os.chdir(os.path.dirname(os.path.abspath(__file__)))

ok = True

try:
    import openmm as mm
    print(f'OpenMM {mm.__version__} | Platforms: {[mm.Platform.getPlatform(i).getName() for i in range(mm.Platform.getNumPlatforms())]}')
except Exception as e:
    ok = False
    print(f'OpenMM failed:\n{e}')

namd = shutil.which('namd3') or shutil.which('namd2')
if namd: print(f'NAMD found: {namd}')
else:
    ok = False
    print('NAMD not found')

print('\nOK' if ok else '\nSomething is missing!')
