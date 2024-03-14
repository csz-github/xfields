// copyright ################################# //
// This file is part of the Xfields Package.   //
// Copyright (c) CERN, 2021.                   //
// ########################################### //

#ifndef XFIELDS_BEAMBEAM3D_METHODS_FOR_STRONGSTRONG_H
#define XFIELDS_BEAMBEAM3D_METHODS_FOR_STRONGSTRONG_H
#include <stdio.h>


/*gpufun*/
void BeamBeamBiGaussian3D_change_ref_frame_local_particle(
        BeamBeamBiGaussian3DData el, LocalParticle* part0){

    // Get data from memory
    double const sin_phi = BeamBeamBiGaussian3DData_get__sin_phi(el);
    double const cos_phi = BeamBeamBiGaussian3DData_get__cos_phi(el);
    double const tan_phi = BeamBeamBiGaussian3DData_get__tan_phi(el);
    double const sin_alpha = BeamBeamBiGaussian3DData_get__sin_alpha(el);
    double const cos_alpha = BeamBeamBiGaussian3DData_get__cos_alpha(el);

    const double shift_x = BeamBeamBiGaussian3DData_get_ref_shift_x(el)
                           + BeamBeamBiGaussian3DData_get_other_beam_shift_x(el);
    const double shift_px = BeamBeamBiGaussian3DData_get_ref_shift_px(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_px(el);
    const double shift_y = BeamBeamBiGaussian3DData_get_ref_shift_y(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_y(el);
    const double shift_py = BeamBeamBiGaussian3DData_get_ref_shift_py(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_py(el);
    const double shift_zeta = BeamBeamBiGaussian3DData_get_ref_shift_zeta(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_zeta(el);
    const double shift_pzeta = BeamBeamBiGaussian3DData_get_ref_shift_pzeta(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_pzeta(el);

    //start_per_particle_block (part0->part)
        double x = LocalParticle_get_x(part);
        double px = LocalParticle_get_px(part);
        double y = LocalParticle_get_y(part);
        double py = LocalParticle_get_py(part);
        double zeta = LocalParticle_get_zeta(part);
        double pzeta = LocalParticle_get_pzeta(part);

        printf("The px value before shift is %f.\n", px);
        printf("The py value before shift is %f.\n", py);

        // Change reference frame
        change_ref_frame_coordinates(
            &x, &px, &y, &py, &zeta, &pzeta,
            shift_x, shift_px, shift_y, shift_py, shift_zeta, shift_pzeta,
            sin_phi, cos_phi, tan_phi, sin_alpha, cos_alpha);

        printf("The px value after shift is %f.\n", px);
        printf("The py value after shift is %f.\n", py);

        // Store
        LocalParticle_set_x(part, x);
        LocalParticle_set_px(part, px);
        LocalParticle_set_y(part, y);
        LocalParticle_set_py(part, py);
        LocalParticle_set_zeta(part, zeta);
        LocalParticle_update_pzeta(part, pzeta);

    //end_per_particle_block

}

/*gpufun*/
void BeamBeamBiGaussian3D_change_back_ref_frame_and_subtract_dipolar_local_particle(
        BeamBeamBiGaussian3DData el, LocalParticle* part0){

    // Get data from memory
    double const sin_phi = BeamBeamBiGaussian3DData_get__sin_phi(el);
    double const cos_phi = BeamBeamBiGaussian3DData_get__cos_phi(el);
    double const tan_phi = BeamBeamBiGaussian3DData_get__tan_phi(el);
    double const sin_alpha = BeamBeamBiGaussian3DData_get__sin_alpha(el);
    double const cos_alpha = BeamBeamBiGaussian3DData_get__cos_alpha(el);

    const double shift_x = BeamBeamBiGaussian3DData_get_ref_shift_x(el)
                           + BeamBeamBiGaussian3DData_get_other_beam_shift_x(el);
    const double shift_px = BeamBeamBiGaussian3DData_get_ref_shift_px(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_px(el);
    const double shift_y = BeamBeamBiGaussian3DData_get_ref_shift_y(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_y(el);
    const double shift_py = BeamBeamBiGaussian3DData_get_ref_shift_py(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_py(el);
    const double shift_zeta = BeamBeamBiGaussian3DData_get_ref_shift_zeta(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_zeta(el);
    const double shift_pzeta = BeamBeamBiGaussian3DData_get_ref_shift_pzeta(el)
                            + BeamBeamBiGaussian3DData_get_other_beam_shift_pzeta(el);

    const double post_subtract_x = BeamBeamBiGaussian3DData_get_post_subtract_x(el);
    const double post_subtract_px = BeamBeamBiGaussian3DData_get_post_subtract_px(el);
    const double post_subtract_y = BeamBeamBiGaussian3DData_get_post_subtract_y(el);
    const double post_subtract_py = BeamBeamBiGaussian3DData_get_post_subtract_py(el);
    const double post_subtract_zeta = BeamBeamBiGaussian3DData_get_post_subtract_zeta(el);
    const double post_subtract_pzeta = BeamBeamBiGaussian3DData_get_post_subtract_pzeta(el);

    //start_per_particle_block (part0->part)
        double x = LocalParticle_get_x(part);
        double px = LocalParticle_get_px(part);
        double y = LocalParticle_get_y(part);
        double py = LocalParticle_get_py(part);
        double zeta = LocalParticle_get_zeta(part);
        double pzeta = LocalParticle_get_pzeta(part);


        // Go back to original reference frame and remove dipolar effect
        change_back_ref_frame_and_subtract_dipolar_coordinates(
            &x, &px, &y, &py, &zeta, &pzeta,
            shift_x, shift_px, shift_y, shift_py, shift_zeta, shift_pzeta,
            post_subtract_x, post_subtract_px,
            post_subtract_y, post_subtract_py,
            post_subtract_zeta, post_subtract_pzeta,
            sin_phi, cos_phi, tan_phi, sin_alpha, cos_alpha);


        printf("The px value after shift back is %f.\n", px);
        printf("The py value after shift back is %f.\n", py);

        // Store
        LocalParticle_set_x(part, x);
        LocalParticle_set_px(part, px);
        LocalParticle_set_y(part, y);
        LocalParticle_set_py(part, py);
        LocalParticle_set_zeta(part, zeta);
        LocalParticle_update_pzeta(part, pzeta);

    //end_per_particle_block

}


/*gpufun*/
void BeamBeam3D_selective_apply_synchrobeam_kick_local_particle(BeamBeamBiGaussian3DData el,
                LocalParticle* part0,
                /*gpuglmem*/ int64_t* i_slice_for_particles){

    //start_per_particle_block (part0->part)

        const int64_t i_slice = i_slice_for_particles[part->ipart];
        const int64_t N_slices = BeamBeamBiGaussian3DData_get_num_slices_other_beam(el);

        if (i_slice >= 0 && i_slice < N_slices){

            double x_star = LocalParticle_get_x(part);
            double px_star = LocalParticle_get_px(part);
            double y_star = LocalParticle_get_y(part);
            double py_star = LocalParticle_get_py(part);
            double zeta_star = LocalParticle_get_zeta(part);
            double pzeta_star = LocalParticle_get_pzeta(part);

            const double q0 = LocalParticle_get_q0(part);
            const double p0c = LocalParticle_get_p0c(part); // eV
            synchrobeam_kick(
                el, part,
                i_slice, q0, p0c,
                &x_star,
                &px_star,
                &y_star,
                &py_star,
                &zeta_star,
                &pzeta_star);


            printf("The px value after kick is %f.\n", px_star);
            printf("The py value after kick is %f.\n", py_star);

            LocalParticle_set_x(part, x_star);
            LocalParticle_set_px(part, px_star);
            LocalParticle_set_y(part, y_star);
            LocalParticle_set_py(part, py_star);
            LocalParticle_set_zeta(part, zeta_star);
            LocalParticle_update_pzeta(part, pzeta_star);

        }

    //end_per_particle_block

}

/*gpufun*/
//void BeamBeam3D_selective_compute_lumi_integral(BeamBeamBiGaussian3DData el,
//                LocalParticle* part0,
          //      /*gpuglmem*/ int64_t timestep,
          //      /*gpuelmem*/ double* lumigrid_my_beam,
          //      /*gpuglmem*/ double* lumigrid_other_beam,
          //      /*gpuglmem*/ int64_t n_lumigrid_cells){
 //   double const intensity1 = BeamBeamBiGaussian3DData_get_beam_intensity(el);
   // double const intensity2 = BeamBeamBiGaussian3DData_get_other_beam_intensity(el);

//  FILE *fp;
  //fp = fopen("../test_lumigrid.txt", "a");
  //const int64_t N_slices = BeamBeamBiGaussian3DData_get_num_slices_other_beam(el);

  // loop over all lumigrids of my beam
  //for (int i_slice=0; i_slice<N_slices; i_slice++){

    // get which other beam slice my slice should interact with
    //int64_t i_slice_other_beam = timestep - i_slice;

    // interact only if my slice is overlapping with other beam slice
    //if (i_slice_other_beam >= 0 && i_slice_other_beam < N_slices){

      // get inex range of my beam
      //int64_t lumigrid_my_beam_slice_start_idx    = n_lumigrid_cells*n_lumigrid_cells * i_slice;
      //int64_t lumigrid_my_beam_slice_end_idx      = n_lumigrid_cells*n_lumigrid_cells * (i_slice+1);
      //int64_t lumigrid_other_beam_slice_start_idx = n_lumigrid_cells*n_lumigrid_cells * i_slice_other_beam;
     // int64_t lumigrid_other_beam_slice_end_idx   = n_lumigrid_cells*n_lumigrid_cells * (i_slice_other_beam+1);

     // fprintf(fp, "timestep: %d - ", timestep);
     // for (int j=lumigrid_my_beam_slice_start_idx; j<lumigrid_my_beam_slice_end_idx; j++){
     //   fprintf(fp, "%g ", lumigrid_my_beam[j]);
      //}
      //fprintf(fp, "- ");
      //for (int j=lumigrid_other_beam_slice_start_idx; j<lumigrid_other_beam_slice_end_idx; j++){
        //fprintf(fp, "%g ", lumigrid_other_beam[j]);
      //}
      //fprintf(fp, "\n");
      //lumicalc(el, lumigrid_my_beam, lumigrid_other_beam, intensity1, intensity2);

      // need to add to total lumi

    //} // end if
  //} // end for
  //fclose(fp);
//}

#endif
