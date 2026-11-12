CIS-1  TUTORIAL 2  -  NVE MOLECULAR DYNAMICS OF A PROTEIN (NAMD + OpenMM)
Thursday 12 Nov 2026, 2:00-3:00 PM, A3 301

READ IN THIS ORDER
  1_BEFORE_CLASS_Install.pdf        Install NAMD and OpenMM. Do this BEFORE class (~20 min).
  2_TUTORIAL.pdf                    The tutorial: every command you type in class, and the questions.
  3_Background_MD_Engines.pdf       Optional reading: what an MD engine is, NAMD vs OpenMM, with pictures.
  4_Cheatsheet_NAMD_vs_OpenMM.pdf   Keep open in class: what each line of nve.namd / nve.py means.
  STEPS_TO_RUN.pdf / .txt           Just the commands, in order (use the .txt for copy-pasting).

FOLDERS
  inputs/              the protein in water (6,215 atoms), read by both programs
                         trpcage_wat.prmtop    topology + force field
                         trpcage_equil.rst7    starting coordinates + box
                         system_prep/          how these were built from the PDB (you can ignore it)
  namd/                nve.namd     NAMD settings. Your output goes to namd/out/
  openmm/              nve.py       OpenMM script
  analysis/            plot_nve.py  plots the energies from both programs
  reference_results/   complete 60 ps runs of both programs, to compare with yours

OTHER FILES
  environment.yml      used by the install guide to create the 'cis1-md' conda environment
  check_install.py     run it after installing: it should print ALL GOOD

NAMD itself is not included (its licence requires free registration). See 1_BEFORE_CLASS_Install.pdf.
