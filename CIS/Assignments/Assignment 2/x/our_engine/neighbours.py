# ### PROVIDED ###

import numpy as np
from scipy.spatial import cKDTree

def pairs_within(pos, box_size, r_list):
    """Fast neighbour search in a periodic box_size.
    **Returns:** (I, J) arrays of all atom pairs `i < j` closer than `r_list (A)` using the minimum image.
    **Usage:**
    Build it with `r_list = cutoff + 2 A` (a 'skin') and reuse it for ~10 steps. Inside every step you still test `r < cutoff` yourself. The coordinates are wrapped into the box only for this search (your own positions stay unwrapped)."""

    w = pos - box_size * np.floor(pos / box_size)  # why can't we: w = min_img(pos, box_size)
    w = np.where(w >= box_size, 0.0, w)

    pairs = cKDTree(w, boxsize=box_size).query_pairs(r_list, output_type='ndarray')

    return pairs[:, 0], pairs[:, 1]

def min_img(d, box_size):
    """Wrap (displacement) vectors into [-L/2, L/2] along each axis of rectangular box."""

    return d - box_size * np.round(d / box_size)
