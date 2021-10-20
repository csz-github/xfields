from scipy.constants import e as qe
import xobjects as xo
import xtrack as xt
import numpy as np

from ..general import _pkg_root

"""
14/10/2021: add x2_bc for ws case. Remove x_CO and delta_x as closed orbit is not explicit here. "x2_bc = x_CO+delta_x"
"""


class BoostParameters(xo.Struct):
    sphi = xo.Float64
    cphi = xo.Float64
    tphi = xo.Float64
    salpha = xo.Float64
    calpha = xo.Float64

class BoostInv3D(xt.BeamElement):
    # C getters will be generated with these names
    _xofields = {
        'boost_parameters': BoostParameters,
       	'alpha': xo.Float64,
	'phi': xo.Float64,
        'x2_bc': xo.Float64,
        'y2_bc': xo.Float64,
        'px2_bc': xo.Float64,
        'py2_bc': xo.Float64,
        'Dx_sub': xo.Float64,
        'Dpx_sub': xo.Float64,
        'Dy_sub': xo.Float64,
        'Dpy_sub': xo.Float64,
        'Dz_sub': xo.Float64,
        'Ddelta_sub': xo.Float64,
	'use_strongstrong': xo.UInt8
 
    }

    def __init__(self,
            _context=None,
            _buffer=None,
            _offset=None,
       	    alpha=0.,
            phi=0., 
            x2_bc=0.,
            y2_bc=0.,
            px2_bc=0.,
            py2_bc=0.,
            Dx_sub=0.,
            Dpx_sub=0.,
            Dy_sub=0.,
            Dpy_sub=0.,
            Dz_sub=0.,
            Ddelta_sub=0.,
	    use_strongstrong=0):
 
        if _context is None:
            _context = context_default

        self.xoinitialize(
                 _context=_context,
                 _buffer=_buffer,
                 _offset=_offset)

        self.x2_bc = x2_bc
        self.y2_bc = y2_bc
        self.px2_bc = px2_bc
        self.py2_bc = py2_bc
        self.Dx_sub = Dx_sub
        self.Dpx_sub = Dpx_sub
        self.Dy_sub = Dy_sub
        self.Dpy_sub= Dpy_sub
        self.Dz_sub = Dz_sub
        self.Ddelta_sub = self.Ddelta_sub
        self.use_strongstrong = use_strongstrong
        self.phi = phi,
        self.alpha = alpha,
        self.boost_parameters = {
                'sphi': np.sin(phi),
                'cphi': np.cos(phi),
                'tphi': np.tan(phi),
                'salpha': np.sin(alpha),
                'calpha': np.cos(alpha)
                }
 
srcs = []
srcs.append(_pkg_root.joinpath('headers/constants.h'))
srcs.append('#define NOFIELDMAP') #TODO Remove this workaound
srcs.append(BoostParameters._gen_c_api()[0]) #TODO This shouldnt be needed
srcs.append(_pkg_root.joinpath('beam_elements/beambeam_src/boostinv3d.h'))

BoostInv3D.XoStruct.extra_sources = srcs
