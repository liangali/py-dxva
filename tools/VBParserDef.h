/**
 * @file VBSParserDef.h
 * @brief Video Bitstream Parser defination declaration
 */


#ifndef _VIDEO_BITSTREAM_PARSER_DEF_H_
#define _VIDEO_BITSTREAM_PARSER_DEF_H_
#include <stdio.h>

enum SYNTAX_PARAMS
{
	SYNTAX_VPS = 0,					/**< @brief The spec vps syntax*/
	SYNTAX_SPS,					/**< @brief The spec sps syntax */
	SYNTAX_PPS,					/**< @brief The spec pps syntax */
	SYNTAX_PICTURE_HEADER,		/**< @brief The spec picture header syntax */
	SYNTAX_APS,					/**< @brief The spec APS syntax */
	SYNTAX_SLICE_HEADER,		/**< @brief The spec Slice Header syntax */
	SLICE_DATA,					/**< @brief The spec Slice Header syntax */
	RPL_STATUS,					/**< @brief The reference picture list status for DPB */
};

typedef struct _SpecDPBParamter
{
	uint32_t dpb_max_dec_pic_buffering_minus1[7] = { 0 };
	uint32_t dpb_max_num_reorder_pics[7] = { 0 };
	uint32_t dpb_max_latency_increase_plus1[7] = { 0 };

}SpecDPBParamter;

typedef struct _SpecSubPic
{
	uint32_t  sps_subpic_ctu_top_left_x;
	uint32_t  sps_subpic_ctu_top_left_y;
	uint32_t sps_subpic_width_minus1;
	uint32_t sps_subpic_height_minus1;
	bool sps_subpic_treated_as_pic_flag;
	bool sps_loop_filter_across_subpic_enabled_flag;
	uint16_t sps_subpic_id;
}SpecSubPic;


typedef struct _SpecWPP
{
	uint32_t luma_log2_weight_denom;
	int delta_chroma_log2_weight_denom;
	uint32_t num_l0_weights;
	bool luma_weight_l0_flag[15];
	bool chroma_weight_l0_flag[15];
	int delta_luma_weight_l0[15];
	int luma_offset_l0[15];
	int delta_chroma_weight_l0[15][2];
	int delta_chroma_offset_l0[15][2];
	uint32_t num_l1_weights;
	bool luma_weight_l1_flag[15];
	bool chroma_weight_l1_flag[15];
	int delta_luma_weight_l1[15];
	int luma_offset_l1[15];
	int delta_chroma_weight_l1[15][2];
	int delta_chroma_offset_l1[15][2];
}SpecWPP;

typedef struct _SpecRPL
{
	int listIdx;
	//int rplIdx;
	/////
	bool rpl_sps_flag;
	uint32_t rpl_idx;
	uint32_t poc_lsb_lt[15];
	bool delta_poc_msb_cycle_present_flag[15];
	uint32_t delta_poc_msb_cycle_lt[15];
	uint32_t ref_frame_poc_list[15];
	/////
	uint32_t num_ref_entries;
	bool ltrp_in_header_flag;
	bool inter_layer_ref_pic_flag[29];
	bool st_ref_pic_flag[29];
	uint32_t abs_delta_poc_st[29];
	bool strp_entry_sign_flag[29];
	uint32_t rpls_poc_lsb_lt[29];
	uint32_t ilrp_idx[29];
}SpecRPL;

typedef struct _SpecRPLS
{
	uint32_t num_ref_entries;
	bool long_term_ref_flag[17];
	int POC[17];
}SpecRPLS;

typedef struct _SpecRefPicture
{
 bool referenced;  //need
 bool usedByCurr; //keep
 bool longTerm;  //need
 int  POC;   //need
 int  layerId; //for multilayer   need
 bool reconstructed;    //need
 bool neededForOutput;    //need
}SpecRefPicture;

typedef struct _SpecRefPicList
{
	SpecRefPicture ref_pic_list[17];
	int num_ref_pic_list;
}SpecRefPicList;

typedef struct _SpecVPS
{
	int vps_video_parameter_set_id;
	uint32_t vps_max_layers_minus1;
	uint32_t vps_max_sublayers_minus1;
	bool vps_default_ptl_dpb_hrd_max_tid_flag;
	bool vps_all_independent_layers_flag;
	uint32_t vps_layer_id[64];
	bool vps_independent_layer_flag[64];
	bool vps_max_tid_ref_present_flag[64];
	bool vps_direct_ref_layer_flag[64][64];
	uint32_t vps_max_tid_il_ref_pics_plus1[64][64];
	bool vps_each_layer_is_an_ols_flag;
	uint32_t vps_ols_mode_idc;
	uint32_t vps_num_output_layer_sets_minus2;
	bool vps_ols_output_layer_flag[256][64];
	uint32_t vps_num_ptls_minus1;
	bool vps_pt_present_flag[256];
	uint32_t vps_ptl_max_tid[256];
	uint32_t vps_ptl_alignment_zero_bit;
	uint32_t vps_ols_ptl_idx[256];
	int vps_num_dpb_params_minus1;
	bool vps_sublayer_dpb_params_present_flag;
	int vps_dpb_max_tid[64];
	uint32_t vps_ols_dpb_pic_width[64];
	uint32_t vps_ols_dpb_pic_height[64];
	uint32_t vps_ols_dpb_chroma_format[64];
	uint32_t vps_ols_dpb_bitdepth_minus8[64];
	int vps_ols_dpb_params_idx[64];
	bool vps_general_hrd_params_present_flag;
	bool vps_timing_hrd_params_present_flag;
	bool vps_sublayer_cpb_params_present_flag;
	uint32_t vps_num_ols_timing_hrd_params_minus1;
	uint32_t vps_hrd_max_tid[256];
	uint32_t vps_ols_timing_hrd_idx[256];
	bool vps_extension_flag;
	bool vps_extension_data_flag;

	SpecDPBParamter    dpb_parameters[256];
}SpecVPS;

typedef struct _SpecSPS
{
	uint32_t sps_seq_parameter_set_id                                       ;
	uint32_t sps_video_parameter_set_id										;
	uint32_t sps_max_sublayers_minus1										;
	uint32_t sps_chroma_format_idc											;
	uint32_t sps_log2_ctu_size_minus5										;
	bool sps_ptl_dpb_hrd_params_present_flag							;
	bool sps_gdr_enabled_flag											;
	bool sps_ref_pic_resampling_enabled_flag							;
	bool sps_res_change_in_clvs_allowed_flag							;
	uint32_t sps_pic_width_max_in_luma_samples								;
	uint32_t sps_pic_height_max_in_luma_samples								;
	bool sps_conformance_window_flag									;
	uint32_t sps_conf_win_left_offset										;
	uint32_t sps_conf_win_right_offset										;
	uint32_t sps_conf_win_top_offset										;
	uint32_t sps_conf_win_bottom_offset										;
	bool sps_subpic_info_present_flag									;
	uint32_t sps_num_subpics_minus1											;
	bool sps_independent_subpics_flag									;
	bool sps_subpic_same_size_flag										;
	SpecSubPic sps_subpic_params[600];
	uint32_t sps_subpic_id_len_minus1										;
	bool sps_subpic_id_mapping_explicitly_signalled_flag				;
	bool sps_subpic_id_mapping_present_flag								;
	uint32_t sps_bitdepth_minus8											;
	bool sps_entropy_coding_sync_enabled_flag							;
	bool sps_entry_point_offsets_present_flag							;
	uint32_t sps_log2_max_pic_order_cnt_lsb_minus4							;
	bool sps_poc_msb_cycle_flag											;
	uint32_t sps_poc_msb_cycle_len_minus1									;
	uint32_t sps_num_extra_ph_bytes											;
	bool sps_extra_ph_bit_present_flag[16]							;
	uint32_t sps_num_extra_sh_bytes											;
	bool sps_extra_sh_bit_present_flag[16]									;
	bool sps_sublayer_dpb_params_flag									;
	uint32_t sps_log2_min_luma_coding_block_size_minus2						;
	bool sps_partition_constraints_override_enabled_flag				;
	uint32_t sps_log2_diff_min_qt_min_cb_intra_slice_luma					;
	uint32_t sps_max_mtt_hierarchy_depth_intra_slice_luma					;
	uint32_t sps_log2_diff_max_bt_min_qt_intra_slice_luma					;
	uint32_t sps_log2_diff_max_tt_min_qt_intra_slice_luma					;
	bool sps_qtbtt_dual_tree_intra_flag									;
	uint32_t sps_log2_diff_min_qt_min_cb_intra_slice_chroma					;
	uint32_t sps_max_mtt_hierarchy_depth_intra_slice_chroma					;
	uint32_t sps_log2_diff_max_bt_min_qt_intra_slice_chroma					;
	uint32_t sps_log2_diff_max_tt_min_qt_intra_slice_chroma					;
	uint32_t sps_log2_diff_min_qt_min_cb_inter_slice						;
	uint32_t sps_max_mtt_hierarchy_depth_inter_slice						;
	uint32_t sps_log2_diff_max_bt_min_qt_inter_slice						;
	uint32_t sps_log2_diff_max_tt_min_qt_inter_slice						;
	bool sps_max_luma_transform_size_64_flag							;
	bool sps_transform_skip_enabled_flag								;
	uint32_t sps_log2_transform_skip_max_size_minus2						;
	bool sps_bdpcm_enabled_flag											;
	bool sps_mts_enabled_flag											;
	bool sps_explicit_mts_intra_enabled_flag							;
	bool sps_explicit_mts_inter_enabled_flag							;
	bool sps_lfnst_enabled_flag											;
	bool sps_joint_cbcr_enabled_flag									;
	bool sps_same_qp_table_for_chroma_flag								;
	int sps_qp_table_start_minus26[3];
	int sps_num_points_in_qp_table_minus1[3];
	int sps_delta_qp_in_val_minus1[3][76];
	int sps_delta_qp_diff_val[3][76];
	bool sps_sao_enabled_flag											;
	bool sps_alf_enabled_flag											;
	bool sps_ccalf_enabled_flag											;
	bool sps_lmcs_enabled_flag											;
	bool sps_weighted_pred_flag											;
	bool sps_weighted_bipred_flag										;
	bool sps_long_term_ref_pics_flag									;
	bool sps_inter_layer_prediction_enabled_flag						;
	bool sps_idr_rpl_present_flag										;
	bool sps_rpl1_same_as_rpl0_flag										;
	uint32_t sps_num_ref_pic_lists[2];
	bool sps_ref_wraparound_enabled_flag								;
	bool sps_temporal_mvp_enabled_flag									;
	bool sps_sbtmvp_enabled_flag										;
	bool sps_amvr_enabled_flag											;
	bool sps_bdof_enabled_flag											;
	bool sps_bdof_control_present_in_ph_flag							;
	bool sps_smvd_enabled_flag											;
	bool sps_dmvr_enabled_flag											;
	bool sps_dmvr_control_present_in_ph_flag							;
	bool sps_mmvd_enabled_flag											;
	bool sps_mmvd_fullpel_only_enabled_flag								;
	uint32_t sps_six_minus_max_num_merge_cand								;
	bool sps_sbt_enabled_flag											;
	bool sps_affine_enabled_flag										;
	uint32_t sps_five_minus_max_num_subblock_merge_cand						;
	bool sps_6param_affine_enabled_flag									;
	bool sps_affine_type_flag;
	bool sps_affine_amvr_enabled_flag									;
	bool sps_affine_prof_enabled_flag									;
	bool sps_prof_control_present_in_ph_flag							;
	bool sps_bcw_enabled_flag 											;
	bool sps_ciip_enabled_flag											;
	bool sps_gpm_enabled_flag											;
	uint32_t sps_max_num_merge_cand_minus_max_num_gpm_cand					;
	uint32_t sps_log2_parallel_merge_level_minus2							;
	bool sps_isp_enabled_flag											;
	bool sps_mrl_enabled_flag											;
	bool sps_mip_enabled_flag											;
	bool sps_cclm_enabled_flag											;
	bool sps_chroma_horizontal_collocated_flag							;
	bool sps_chroma_vertical_collocated_flag							;
	bool sps_palette_enabled_flag										;
	bool sps_act_enabled_flag											;
	uint32_t sps_min_qp_prime_ts											;
	bool sps_ibc_enabled_flag											;
	uint32_t sps_six_minus_max_num_ibc_merge_cand							;
	bool sps_ladf_enabled_flag											;
	uint32_t sps_num_ladf_intervals_minus2									;
	uint32_t sps_ladf_lowest_interval_qp_offset								;
	uint32_t sps_ladf_qp_offset[5];
	uint32_t sps_ladf_delta_threshold_minus1[5];
	bool sps_explicit_scaling_list_enabled_flag							;
	bool sps_scaling_matrix_for_lfnst_disabled_flag						;
	bool sps_scaling_matrix_for_alternative_colour_space_disabled_flag	;
	bool sps_scaling_matrix_designated_colour_space_flag				;
	bool sps_dep_quant_enabled_flag										;
	bool sps_sign_data_hiding_enabled_flag								;
	bool sps_virtual_boundaries_enabled_flag							;
	bool sps_virtual_boundaries_present_flag							;
	uint32_t sps_num_ver_virtual_boundaries									;
	uint32_t sps_virtual_boundary_pos_x_minus1[3]							;
	uint32_t sps_num_hor_virtual_boundaries									;
	uint32_t sps_virtual_boundary_pos_y_minus1[3]							;
	bool sps_timing_hrd_params_present_flag								;
	bool sps_sublayer_cpb_params_present_flag							;
	bool sps_field_seq_flag												;
	bool sps_vui_parameters_present_flag								;
	uint32_t sps_vui_payload_size_minus1									;
	uint32_t sps_vui_alignment_zero_bit										;
	bool sps_extension_flag												;
	bool sps_extension_data_flag[8];
	SpecDPBParamter    dpb_parameters;

	SpecRPL sps_rpl[2][64];
	int rplNum[2];
}SpecSPS;

typedef struct _SpecSliceStruct
{
	uint32_t pps_slice_width_in_tiles_minus1;
	uint32_t pps_slice_height_in_tiles_minus1;
	uint32_t pps_num_exp_slices_in_tile;
	uint32_t SliceTopLeftTileIdx;
	uint32_t pps_exp_slice_height_in_ctus_minus1;
}SpecSliceStruct;

typedef struct _SpecPPS
{
	uint32_t pps_pic_parameter_set_id;
	uint32_t pps_seq_parameter_set_id;
	bool pps_mixed_nalu_types_in_pic_flag;
	uint32_t pps_pic_width_in_luma_samples;
	uint32_t pps_pic_height_in_luma_samples;
	bool pps_conformance_window_flag;
	int pps_conf_win_left_offset;
	int pps_conf_win_right_offset;
	int pps_conf_win_top_offset;
	int pps_conf_win_bottom_offset;
	bool pps_scaling_window_explicit_signalling_flag;
	int pps_scaling_win_left_offset;
	int pps_scaling_win_right_offset;
	int pps_scaling_win_top_offset;
	int pps_scaling_win_bottom_offset;
	bool pps_output_flag_present_flag;
	bool pps_no_pic_partition_flag;
	bool pps_subpic_id_mapping_present_flag;
	uint32_t pps_num_subpics_minus1;
	uint32_t pps_subpic_id_len_minus1;
	uint16_t pps_subpic_id[600];
	uint32_t pps_log2_ctu_size_minus5;
	uint32_t pps_num_exp_tile_columns_minus1;
	uint32_t pps_num_exp_tile_rows_minus1;
	uint32_t pps_tile_column_width_minus1[30];
	uint32_t pps_tile_row_height_minus1[440];
	bool pps_loop_filter_across_tiles_enabled_flag;
	bool pps_rect_slice_flag;
	bool pps_single_slice_per_subpic_flag;
	uint32_t pps_num_slices_in_pic_minus1;
	bool pps_tile_idx_delta_present_flag;
	SpecSliceStruct pps_slice_struct[600];
	int pps_tile_idx_delta_val[600];
	bool pps_loop_filter_across_slices_enabled_flag;
	bool pps_cabac_init_present_flag;
	uint32_t pps_num_ref_idx_default_active_minus1[2];
	bool pps_rpl1_idx_present_flag;
	bool pps_weighted_pred_flag;
	bool pps_weighted_bipred_flag;
	bool pps_ref_wraparound_enabled_flag;
	int pps_pic_width_minus_wraparound_offset;
	int pps_init_qp_minus26;
	bool pps_cu_qp_delta_enabled_flag;
	bool pps_chroma_tool_offsets_present_flag;
	int pps_cb_qp_offset;
	int pps_cr_qp_offset;
	bool pps_joint_cbcr_qp_offset_present_flag;
	int pps_joint_cbcr_qp_offset_value;
	bool pps_slice_chroma_qp_offsets_present_flag;
	bool pps_cu_chroma_qp_offset_list_enabled_flag;
	uint32_t pps_chroma_qp_offset_list_len_minus1;
	int pps_cb_qp_offset_list[6];
	int pps_cr_qp_offset_list[6];
	int pps_joint_cbcr_qp_offset_list[6];
	bool pps_deblocking_filter_control_present_flag;
	bool pps_deblocking_filter_override_enabled_flag;
	bool pps_deblocking_filter_disabled_flag;
	bool pps_dbf_info_in_ph_flag;
	int pps_luma_beta_offset_div2;
	int pps_luma_tc_offset_div2;
	int pps_cb_beta_offset_div2;
	int pps_cb_tc_offset_div2;
	int pps_cr_beta_offset_div2;
	int pps_cr_tc_offset_div2;
	bool pps_rpl_info_in_ph_flag;
	bool pps_sao_info_in_ph_flag;
	bool pps_alf_info_in_ph_flag;
	bool pps_wp_info_in_ph_flag;
	bool pps_qp_delta_info_in_ph_flag;
	bool pps_picture_header_extension_present_flag;
	bool pps_slice_header_extension_present_flag;
	bool pps_extension_flag;
	bool pps_extension_data_flag;
}SpecPPS;

typedef struct _SpecPictureHeader
{
	bool ph_gdr_or_irap_pic_flag;
	bool ph_non_ref_pic_flag;
	bool ph_gdr_pic_flag;
	bool ph_inter_slice_allowed_flag;
	bool ph_intra_slice_allowed_flag;
	uint32_t ph_pic_parameter_set_id;
	uint32_t ph_pic_order_cnt_lsb;
	uint32_t ph_recovery_poc_cnt;
	uint32_t ph_extra_bit[16];
	bool ph_poc_msb_cycle_present_flag;
	uint32_t ph_poc_msb_cycle_val;
	bool ph_alf_enabled_flag;
	uint32_t ph_num_alf_aps_ids_luma;
	uint32_t ph_alf_aps_id_luma[7];
	bool ph_alf_cb_enabled_flag;
	bool ph_alf_cr_enabled_flag;
	uint32_t ph_alf_aps_id_chroma;
	bool ph_alf_cc_cb_enabled_flag;
	uint32_t ph_alf_cc_cb_aps_id;
	bool ph_alf_cc_cr_enabled_flag;
	uint32_t ph_alf_cc_cr_aps_id;
	bool ph_lmcs_enabled_flag;
	uint32_t ph_lmcs_aps_id;
	bool ph_chroma_residual_scale_flag;
	bool ph_explicit_scaling_list_enabled_flag;
	uint32_t ph_scaling_list_aps_id;
	bool ph_virtual_boundaries_present_flag;
	uint32_t ph_num_ver_virtual_boundaries;
	uint32_t ph_virtual_boundary_pos_x_minus1[3];
	uint32_t ph_num_hor_virtual_boundaries;
	uint32_t ph_virtual_boundary_pos_y_minus1[3];
	bool ph_pic_output_flag;
	bool ph_partition_constraints_override_flag;
	uint32_t ph_log2_diff_min_qt_min_cb_intra_slice_luma;
	uint32_t ph_max_mtt_hierarchy_depth_intra_slice_luma;
	uint32_t ph_log2_diff_max_bt_min_qt_intra_slice_luma;
	uint32_t ph_log2_diff_max_tt_min_qt_intra_slice_luma;
	uint32_t ph_log2_diff_min_qt_min_cb_intra_slice_chroma;
	uint32_t ph_max_mtt_hierarchy_depth_intra_slice_chroma;
	uint32_t ph_log2_diff_max_bt_min_qt_intra_slice_chroma;
	uint32_t ph_log2_diff_max_tt_min_qt_intra_slice_chroma;
	uint32_t ph_cu_qp_delta_subdiv_intra_slice;
	uint32_t ph_cu_chroma_qp_offset_subdiv_intra_slice;
	uint32_t ph_log2_diff_min_qt_min_cb_inter_slice;
	uint32_t ph_max_mtt_hierarchy_depth_inter_slice;
	uint32_t ph_log2_diff_max_bt_min_qt_inter_slice;
	uint32_t ph_log2_diff_max_tt_min_qt_inter_slice;
	uint32_t ph_cu_qp_delta_subdiv_inter_slice;
	uint32_t ph_cu_chroma_qp_offset_subdiv_inter_slice;
	bool ph_temporal_mvp_enabled_flag;
	bool ph_collocated_from_l0_flag;
	uint32_t ph_collocated_ref_idx;
	bool ph_mmvd_fullpel_only_flag;
	bool ph_mvd_l1_zero_flag;
	bool ph_bdof_disabled_flag;
	bool ph_dmvr_disabled_flag;
	bool ph_prof_disabled_flag;
	int ph_qp_delta;
	bool ph_joint_cbcr_sign_flag;
	bool ph_sao_luma_enabled_flag;
	bool ph_sao_chroma_enabled_flag;
	bool ph_deblocking_params_present_flag;
	bool ph_deblocking_filter_disabled_flag;
	int ph_luma_beta_offset_div2;
	int ph_luma_tc_offset_div2;
	int ph_cb_beta_offset_div2;
	int ph_cb_tc_offset_div2;
	int ph_cr_beta_offset_div2;
	int ph_cr_tc_offset_div2;
	uint32_t ph_extension_length;
	uint32_t ph_extension_data_byte[256];
	bool NumRefEntriesRplIdx0LargerThan0;
	bool NumRefEntriesRplIdx1LargerThan0;

	SpecRPL ph_rpl[2];
	SpecWPP ph_wpp;
}SpecPictureHeader;


typedef struct _SpecAlf
{
	uint32_t aps_params_type;
	uint32_t aps_adaptation_parameter_set_id;
	bool aps_chroma_present_flag;
	bool aps_extension_flag;
	bool aps_extension_data_flag;

	bool alf_luma_filter_signal_flag;
	bool alf_chroma_filter_signal_flag;
	bool alf_cc_cb_filter_signal_flag;
	bool alf_cc_cr_filter_signal_flag;
	bool alf_luma_clip_flag;
	uint32_t alf_luma_num_filters_signalled_minus1;
	uint32_t alf_luma_coeff_delta_idx[25];
	uint32_t alf_luma_coeff_abs[25][12];
	uint32_t alf_luma_coeff_sign[25][12];
	uint32_t alf_luma_clip_idx[25][12];
	bool alf_chroma_clip_flag;
	uint32_t alf_chroma_num_alt_filters_minus1;
	uint32_t alf_chroma_coeff_abs[8][6];
	uint32_t alf_chroma_coeff_sign[8][6];
	uint32_t alf_chroma_clip_idx[8][6];
	uint32_t alf_cc_cb_filters_signalled_minus1;
	uint32_t alf_cc_cb_mapped_coeff_abs[4][7];
	uint32_t alf_cc_cb_coeff_sign[4][7];
	uint32_t alf_cc_cr_filters_signalled_minus1;
	uint32_t alf_cc_cr_mapped_coeff_abs[4][7];
	uint32_t alf_cc_cr_coeff_sign[4][7];
}SpecAlf;

typedef struct _SpecLmcs
{
	uint32_t aps_params_type;
	uint32_t aps_adaptation_parameter_set_id;
	bool aps_chroma_present_flag;
	bool aps_extension_flag;
	bool aps_extension_data_flag;

	uint32_t lmcs_min_bin_idx;
	uint32_t lmcs_delta_max_bin_idx;
	uint32_t lmcs_delta_cw_prec_minus1;
	uint32_t lmcs_delta_abs_cw[16];
	bool lmcs_delta_sign_cw_flag[16];
	uint32_t lmcs_delta_abs_crs;
	bool lmcs_delta_sign_crs_flag;
}SpecLmcs;

typedef struct _SpecScalingList
{
	uint32_t aps_params_type;
	uint32_t aps_adaptation_parameter_set_id;
	bool aps_chroma_present_flag;
	bool aps_extension_flag;
	bool aps_extension_data_flag;

	bool scaling_list_copy_mode_flag[30];
	bool scaling_list_pred_mode_flag[30];
	uint32_t scaling_list_pred_id_delta[30];
	int scaling_list_dc_coef[30];
	int scaling_list_delta_coef[30][64];

	int		ScalingMatrixDCRec[14];				// [1..255]
	int		ScalingMatrixRec2x2[2][2][2];			// [1..255]
	int		ScalingMatrixRec4x4[6][4][4];			// [1..255]
	int		ScalingMatrixRec8x8[20][8][8];		// [1..255]

}SpecScalingList;

typedef struct _SpecAPS
{
	SpecAlf aps_alf[8];
	SpecLmcs aps_lmcs[8];
	SpecScalingList aps_scaling_list[4];
	int alfNum;
	int lmcsNum;
	int scalingListNum;
}SpecAPS;

typedef struct _SpecSliceHeader
{
	bool sh_picture_header_in_slice_header_flag;
	uint32_t sh_subpic_id;
	uint32_t sh_slice_address;
	uint32_t sh_extra_bit[16];
	uint32_t sh_num_tiles_in_slice_minus1;
	uint32_t sh_slice_type;
	bool sh_no_output_of_prior_pics_flag;
	bool sh_alf_enabled_flag;
	uint32_t sh_num_alf_aps_ids_luma;
	int sh_alf_aps_id_luma[7];
	bool sh_alf_cb_enabled_flag;
	bool sh_alf_cr_enabled_flag;
	uint32_t sh_alf_aps_id_chroma;
	bool sh_alf_cc_cb_enabled_flag;
	uint32_t sh_alf_cc_cb_aps_id;
	bool sh_alf_cc_cr_enabled_flag;
	uint32_t sh_alf_cc_cr_aps_id;
	bool sh_lmcs_used_flag;
	bool sh_explicit_scaling_list_used_flag;
	bool sh_num_ref_idx_active_override_flag;
	uint32_t sh_num_ref_idx_active_minus1[2];
	bool sh_cabac_init_flag;
	bool sh_collocated_from_l0_flag;
	uint32_t sh_collocated_ref_idx;
	uint32_t sh_qp_delta;
	int sh_cb_qp_offset;
	int sh_cr_qp_offset;
	int sh_joint_cbcr_qp_offset;
	bool sh_cu_chroma_qp_offset_enabled_flag;
	bool sh_sao_luma_used_flag;
	bool sh_sao_chroma_used_flag;
	bool sh_deblocking_params_present_flag;
	bool sh_deblocking_filter_disabled_flag;
	int sh_luma_beta_offset_div2;
	int sh_luma_tc_offset_div2;
	int sh_cb_beta_offset_div2;
	int sh_cb_tc_offset_div2;
	int sh_cr_beta_offset_div2;
	int sh_cr_tc_offset_div2;
	bool sh_dep_quant_used_flag;
	bool sh_sign_data_hiding_used_flag;
	bool sh_ts_residual_coding_disabled_flag;
	uint32_t sh_slice_header_extension_length;
	uint32_t sh_slice_header_extension_data_byte[256];
	uint32_t sh_entry_offset_len_minus1;
	uint32_t sh_entry_point_offset_minus1[512];
	int curPocVal;
	bool NoBackwardPredFlag;
	uint32_t NumEntryPoints;
	SpecRPLS sh_rpls[2];
	SpecRPL sh_rpl[2];
	SpecWPP sh_wpp;
}SpecSliceHeader;

typedef struct _Data
{
	uint8_t* data;
	uint32_t dataSize;
	int sliceDataOffset;
}Data;

typedef struct _SliceData
{
	Data sliceData[600];
	int numSlice;
}SliceData;

typedef struct _SpecSliceHeaderArray
{
	SpecSliceHeader *sliceHeader[600];
	int numSlice;
}SpecSliceHeaderArray;

typedef struct _SpecSPSArray
{
	SpecSPS *sps[16];
	int numSPS;
}SpecSPSArray;

typedef struct _SpecPPSArray
{
	SpecPPS *pps[64];
	int numPPS;
}SpecPPSArray;

typedef struct _SpecVPSArray
{
	SpecVPS *vps[16];
	int numVPS;
}SpecVPSArray;


#endif //_VIDEO_BITSTREAM_PARSER_DEF_H_
