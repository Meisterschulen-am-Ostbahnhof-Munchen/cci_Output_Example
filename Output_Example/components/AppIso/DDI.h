/*
 * DDI.h
 *
 *  Created on: 01.02.2018
 *      Author: hoepffr
 */

#ifndef DDI_H_
#define DDI_H_

#define DDI_DATA_DICTIONARY_VERSION	0	 // 0 - Data Dictionary Version
#define DDI_SETPOINT_VOLUME_PER_AREA_APPLICATION_RATE	1	 // 1 - Setpoint Volume Per Area Application Rate as [mm³/m²]
#define DDI_ACTUAL_VOLUME_PER_AREA_APPLICATION_RATE	2	 // 2 - Actual Volume Per Area Application Rate as [mm³/m²]
#define DDI_DEFAULT_VOLUME_PER_AREA_APPLICATION_RATE	3	 // 3 - Default Volume Per Area Application Rate as [mm³/m²]
#define DDI_MINIMUM_VOLUME_PER_AREA_APPLICATION_RATE	4	 // 4 - Minimum Volume Per Area Application Rate as [mm³/m²]
#define DDI_MAXIMUM_VOLUME_PER_AREA_APPLICATION_RATE	5	 // 5 - Maximum Volume Per Area Application Rate as [mm³/m²]
#define DDI_SETPOINT_MASS_PER_AREA_APPLICATION_RATE	6	 // 6 - Setpoint Mass Per Area Application Rate
#define DDI_ACTUAL_MASS_PER_AREA_APPLICATION_RATE	7	 // 7 - Actual Mass Per Area Application Rate
#define DDI_DEFAULT_MASS_PER_AREA_APPLICATION_RATE	8	 // 8 - Default Mass Per Area Application Rate
#define DDI_MINIMUM_MASS_PER_AREA_APPLICATION_RATE	9	 // 9 - Minimum Mass Per Area Application Rate
#define DDI_MAXIMUM_MASS_PER_AREA_APPLICATION_RATE	10	 // 10 - Maximum Mass Per Area Application Rate
#define DDI_SETPOINT_COUNT_PER_AREA_APPLICATION_RATE	11	 // 11 - Setpoint Count Per Area Application Rate
#define DDI_ACTUAL_COUNT_PER_AREA_APPLICATION_RATE	12	 // 12 - Actual Count Per Area Application Rate
#define DDI_DEFAULT_COUNT_PER_AREA_APPLICATION_RATE	13	 // 13 - Default Count Per Area Application Rate
#define DDI_MINIMUM_COUNT_PER_AREA_APPLICATION_RATE	14	 // 14 - Minimum Count Per Area Application Rate
#define DDI_MAXIMUM_COUNT_PER_AREA_APPLICATION_RATE	15	 // 15 - Maximum Count Per Area Application Rate
#define DDI_SETPOINT_SPACING_APPLICATION_RATE	16	 // 16 - Setpoint Spacing Application Rate
#define DDI_ACTUAL_SPACING_APPLICATION_RATE	17	 // 17 - Actual Spacing Application Rate
#define DDI_DEFAULT_SPACING_APPLICATION_RATE	18	 // 18 - Default Spacing Application Rate
#define DDI_MINIMUM_SPACING_APPLICATION_RATE	19	 // 19 - Minimum Spacing Application Rate
#define DDI_MAXIMUM_SPACING_APPLICATION_RATE	20	 // 20 - Maximum Spacing Application Rate
#define DDI_SETPOINT_VOLUME_PER_VOLUME_APPLICATION_RATE	21	 // 21 - Setpoint Volume Per Volume Application Rate
#define DDI_ACTUAL_VOLUME_PER_VOLUME_APPLICATION_RATE	22	 // 22 - Actual Volume Per Volume Application Rate
#define DDI_DEFAULT_VOLUME_PER_VOLUME_APPLICATION_RATE	23	 // 23 - Default Volume Per Volume Application Rate
#define DDI_MINIMUM_VOLUME_PER_VOLUME_APPLICATION_RATE	24	 // 24 - Minimum Volume Per Volume Application Rate
#define DDI_MAXIMUM_VOLUME_PER_VOLUME_APPLICATION_RATE	25	 // 25 - Maximum Volume Per Volume Application Rate
#define DDI_SETPOINT_MASS_PER_MASS_APPLICATION_RATE	26	 // 26 - Setpoint Mass Per Mass Application Rate
#define DDI_ACTUAL_MASS_PER_MASS_APPLICATION_RATE	27	 // 27 - Actual Mass Per Mass Application Rate
#define DDI_DEFAULT_MASS_PER_MASS_APPLICATION_RATE	28	 // 28 - Default Mass Per Mass Application Rate
#define DDI_MINIMUM_MASS_PER_MASS_APPLICATION_RATE	29	 // 29 - Minimum Mass Per Mass Application Rate
#define DDI_MAXIMUMMASS_PER_MASS_APPLICATION_RATE	30	 // 30 - MaximumMass Per Mass Application Rate
#define DDI_SETPOINT_VOLUME_PER_MASS_APPLICATION_RATE	31	 // 31 - Setpoint Volume Per Mass Application Rate
#define DDI_ACTUAL_VOLUME_PER_MASS_APPLICATION_RATE	32	 // 32 - Actual Volume Per Mass Application Rate
#define DDI_DEFAULT_VOLUME_PER_MASS_APPLICATION_RATE	33	 // 33 - Default Volume Per Mass Application Rate
#define DDI_MINIMUM_VOLUME_PER_MASS_APPLICATION_RATE	34	 // 34 - Minimum Volume Per Mass Application Rate
#define DDI_MAXIMUM_VOLUME_PER_MASS_APPLICATION_RATE	35	 // 35 - Maximum Volume Per Mass Application Rate
#define DDI_SETPOINT_VOLUME_PER_TIME_APPLICATION_RATE	36	 // 36 - Setpoint Volume Per Time Application Rate
#define DDI_ACTUAL_VOLUME_PER_TIME_APPLICATION_RATE	37	 // 37 - Actual Volume Per Time Application Rate
#define DDI_DEFAULT_VOLUME_PER_TIME_APPLICATION_RATE	38	 // 38 - Default Volume Per Time Application Rate
#define DDI_MINIMUM_VOLUME_PER_TIME_APPLICATION_RATE	39	 // 39 - Minimum Volume Per Time Application Rate
#define DDI_MAXIMUM_VOLUME_PER_TIME_APPLICATION_RATE	40	 // 40 - Maximum Volume Per Time Application Rate
#define DDI_SETPOINT_MASS_PER_TIME_APPLICATION_RATE	41	 // 41 - Setpoint Mass Per Time Application Rate
#define DDI_ACTUAL_MASS_PER_TIME_APPLICATION_RATE	42	 // 42 - Actual Mass Per Time Application Rate
#define DDI_DEFAULT_MASS_PER_TIME_APPLICATION_RATE	43	 // 43 - Default Mass Per Time Application Rate
#define DDI_MINIMUM_MASS_PER_TIME_APPLICATION_RATE	44	 // 44 - Minimum Mass Per Time Application Rate
#define DDI_MAXIMUM_MASS_PER_TIME_APPLICATION_RATE	45	 // 45 - Maximum Mass Per Time Application Rate
#define DDI_SETPOINT_COUNT_PER_TIME_APPLICATION_RATE	46	 // 46 - Setpoint Count Per Time Application Rate
#define DDI_ACTUAL_COUNT_PER_TIME_APPLICATION_RATE	47	 // 47 - Actual Count Per Time Application Rate
#define DDI_DEFAULT_COUNT_PER_TIME_APPLICATION_RATE	48	 // 48 - Default Count Per Time Application Rate
#define DDI_MINIMUM_COUNT_PER_TIME_APPLICATION_RATE	49	 // 49 - Minimum Count Per Time Application Rate
#define DDI_MAXIMUM_COUNT_PER_TIME_APPLICATION_RATE	50	 // 50 - Maximum Count Per Time Application Rate
#define DDI_SETPOINT_TILLAGE_DEPTH	51	 // 51 - Setpoint Tillage Depth
#define DDI_ACTUAL_TILLAGE_DEPTH	52	 // 52 - Actual Tillage Depth
#define DDI_DEFAULT_TILLAGE_DEPTH	53	 // 53 - Default Tillage Depth
#define DDI_MINIMUM_TILLAGE_DEPTH	54	 // 54 - Minimum Tillage Depth
#define DDI_MAXIMUM_TILLAGE_DEPTH	55	 // 55 - Maximum Tillage Depth
#define DDI_SETPOINT_SEEDING_DEPTH	56	 // 56 - Setpoint Seeding Depth
#define DDI_ACTUAL_SEEDING_DEPTH	57	 // 57 - Actual Seeding Depth
#define DDI_DEFAULT_SEEDING_DEPTH	58	 // 58 - Default Seeding Depth
#define DDI_MINIMUM_SEEDING_DEPTH	59	 // 59 - Minimum Seeding Depth
#define DDI_MAXIMUM_SEEDING_DEPTH	60	 // 60 - Maximum Seeding Depth
#define DDI_SETPOINT_WORKING_HEIGHT	61	 // 61 - Setpoint Working Height
#define DDI_ACTUAL_WORKING_HEIGHT	62	 // 62 - Actual Working Height
#define DDI_DEFAULT_WORKING_HEIGHT	63	 // 63 - Default Working Height
#define DDI_MINIMUM_WORKING_HEIGHT	64	 // 64 - Minimum Working Height
#define DDI_MAXIMUM_WORKING_HEIGHT	65	 // 65 - Maximum Working Height
#define DDI_SETPOINT_WORKING_WIDTH	66	 // 66 - Setpoint Working Width
#define DDI_ACTUAL_WORKING_WIDTH	67	 // 67 - Actual Working Width
#define DDI_DEFAULT_WORKING_WIDTH	68	 // 68 - Default Working Width
#define DDI_MINIMUM_WORKING_WIDTH	69	 // 69 - Minimum Working Width
#define DDI_MAXIMUM_WORKING_WIDTH	70	 // 70 - Maximum Working Width
#define DDI_SETPOINT_VOLUME_CONTENT	71	 // 71 - Setpoint Volume Content
#define DDI_ACTUAL_VOLUME_CONTENT	72	 // 72 - Actual Volume Content
#define DDI_MAXIMUM_VOLUME_CONTENT	73	 // 73 - Maximum Volume Content
#define DDI_SETPOINT_MASS_CONTENT	74	 // 74 - Setpoint Mass Content
#define DDI_ACTUAL_MASS_CONTENT	75	 // 75 - Actual Mass Content
#define DDI_MAXIMUM_MASS_CONTENT	76	 // 76 - Maximum Mass Content
#define DDI_SETPOINT_COUNT_CONTENT	77	 // 77 - Setpoint Count Content
#define DDI_ACTUAL_COUNT_CONTENT	78	 // 78 - Actual Count Content
#define DDI_MAXIMUM_COUNT_CONTENT	79	 // 79 - Maximum Count Content
#define DDI_APPLICATION_TOTAL_VOLUME_AS_L	80	 // 80 - Application Total Volume as [L]
#define DDI_APPLICATION_TOTAL_MASS_IN_KG	81	 // 81 - Application Total Mass in [kg]
#define DDI_APPLICATION_TOTAL_COUNT	82	 // 82 - Application Total Count
#define DDI_VOLUME_PER_AREA_YIELD	83	 // 83 - Volume Per Area Yield
#define DDI_MASS_PER_AREA_YIELD	84	 // 84 - Mass Per Area Yield
#define DDI_COUNT_PER_AREA_YIELD	85	 // 85 - Count Per Area Yield
#define DDI_VOLUME_PER_TIME_YIELD	86	 // 86 - Volume Per Time Yield
#define DDI_MASS_PER_TIME_YIELD	87	 // 87 - Mass Per Time Yield
#define DDI_COUNT_PER_TIME_YIELD	88	 // 88 - Count Per Time Yield
#define DDI_YIELD_TOTAL_VOLUME	89	 // 89 - Yield Total Volume
#define DDI_YIELD_TOTAL_MASS	90	 // 90 - Yield Total Mass
#define DDI_YIELD_TOTAL_COUNT	91	 // 91 - Yield Total Count
#define DDI_VOLUME_PER_AREA_CROP_LOSS	92	 // 92 - Volume Per Area Crop Loss
#define DDI_MASS_PER_AREA_CROP_LOSS	93	 // 93 - Mass Per Area Crop Loss
#define DDI_COUNT_PER_AREA_CROP_LOSS	94	 // 94 - Count Per Area Crop Loss
#define DDI_VOLUME_PER_TIME_CROP_LOSS	95	 // 95 - Volume Per Time Crop Loss
#define DDI_MASS_PER_TIME_CROP_LOSS	96	 // 96 - Mass Per Time Crop Loss
#define DDI_COUNT_PER_TIME_CROP_LOSS	97	 // 97 - Count Per Time Crop Loss
#define DDI_PERCENTAGE_CROP_LOSS	98	 // 98 - Percentage Crop Loss
#define DDI_CROP_MOISTURE	99	 // 99 - Crop Moisture
#define DDI_CROP_CONTAMINATION	100	 // 100 - Crop Contamination
#define DDI_SETPOINT_BALE_WIDTH	101	 // 101 - Setpoint Bale Width
#define DDI_ACTUAL_BALE_WIDTH	102	 // 102 - Actual Bale Width
#define DDI_DEFAULT_BALE_WIDTH	103	 // 103 - Default Bale Width
#define DDI_MINIMUM_BALE_WIDTH	104	 // 104 - Minimum Bale Width
#define DDI_MAXIMUM_BALE_WIDTH	105	 // 105 - Maximum Bale Width
#define DDI_SETPOINT_BALE_HEIGHT	106	 // 106 - Setpoint Bale Height
#define DDI_ACTUALBALEHEIGHT	107	 // 107 - ActualBaleHeight
#define DDI_DEFAULT_BALE_HEIGHT	108	 // 108 - Default Bale Height
#define DDI_MINIMUM_BALE_HEIGHT	109	 // 109 - Minimum Bale Height
#define DDI_MAXIMUM_BALE_HEIGHT	110	 // 110 - Maximum Bale Height
#define DDI_SETPOINT_BALE_SIZE	111	 // 111 - Setpoint Bale Size
#define DDI_ACTUAL_BALE_SIZE	112	 // 112 - Actual Bale Size
#define DDI_DEFAULT_BALE_SIZE	113	 // 113 - Default Bale Size
#define DDI_MINIMUM_BALE_SIZE	114	 // 114 - Minimum Bale Size
#define DDI_MAXIMUM_BALE_SIZE	115	 // 115 - Maximum Bale Size
#define DDI_TOTAL_AREA	116	 // 116 - Total Area
#define DDI_EFFECTIVE_TOTAL_DISTANCE	117	 // 117 - Effective Total Distance
#define DDI_INEFFECTIVE_TOTAL_DISTANCE	118	 // 118 - Ineffective Total Distance
#define DDI_EFFECTIVE_TOTAL_TIME	119	 // 119 - Effective Total Time
#define DDI_INEFFECTIVE_TOTAL_TIME	120	 // 120 - Ineffective Total Time
#define DDI_PRODUCT_DENSITY_MASS_PER_VOLUME	121	 // 121 - Product Density Mass Per Volume
#define DDI_PRODUCT_DENSITY_MASS_PERCOUNT	122	 // 122 - Product Density Mass PerCount
#define DDI_PRODUCT_DENSITY_VOLUME_PER_COUNT	123	 // 123 - Product Density Volume Per Count
#define DDI_AUXILIARY_VALVE_SCALING_EXTEND	124	 // 124 - Auxiliary Valve Scaling Extend
#define DDI_AUXILIARY_VALVE_SCALING_RETRACT	125	 // 125 - Auxiliary Valve Scaling Retract
#define DDI_AUXILIARY_VALVE_RAMP_EXTEND_UP	126	 // 126 - Auxiliary Valve Ramp Extend Up
#define DDI_AUXILIARY_VALVE_RAMP_EXTEND_DOWN	127	 // 127 - Auxiliary Valve Ramp Extend Down
#define DDI_AUXILIARY_VALVE_RAMP_RETRACT_UP	128	 // 128 - Auxiliary Valve Ramp Retract Up
#define DDI_AUXILIARY_VALVE_RAMP_RETRACT_DOWN	129	 // 129 - Auxiliary Valve Ramp Retract Down
#define DDI_AUXILIARY_VALVE_FLOAT_THRESHOLD	130	 // 130 - Auxiliary Valve Float Threshold
#define DDI_AUXILIARY_VALVE_PROGRESSIVITY_EXTEND	131	 // 131 - Auxiliary Valve Progressivity Extend
#define DDI_AUXILIARY_VALVE_PROGRESSIVITY_RETRACT	132	 // 132 - Auxiliary Valve Progressivity Retract
#define DDI_AUXILIARY_VALVE_INVERT_PORTS	133	 // 133 - Auxiliary Valve Invert Ports
#define DDI_DEVICE_ELEMENT_OFFSET_X	134	 // 134 - Device Element Offset X
#define DDI_DEVICE_ELEMENT_OFFSET_Y	135	 // 135 - Device Element Offset Y
#define DDI_DEVICE_ELEMENT_OFFSET_Z	136	 // 136 - Device Element Offset Z
#define DDI_DEVICE_VOLUME_CAPACITY	137	 // 137 - Device Volume Capacity
#define DDI_DEVICE_MASS_CAPACITY	138	 // 138 - Device Mass Capacity
#define DDI_DEVICE_COUNT_CAPACITY	139	 // 139 - Device Count Capacity
#define DDI_SETPOINT_PERCENTAGE_APPLICATION_RATE	140	 // 140 - Setpoint Percentage Application Rate
#define DDI_ACTUAL_WORK_STATE	141	 // 141 - Actual Work State
#define DDI_PHYSICAL_SETPOINT_TIME_LATENCY	142	 // 142 - Physical Setpoint Time Latency
#define DDI_PHYSICAL_ACTUAL_VALUE_TIME_LATENCY	143	 // 143 - Physical Actual Value Time Latency
#define DDI_YAW_ANGLE	144	 // 144 - Yaw Angle
#define DDI_ROLL_ANGLE	145	 // 145 - Roll Angle
#define DDI_PITCH_ANGLE	146	 // 146 - Pitch Angle
#define DDI_LOG_COUNT	147	 // 147 - Log Count
#define DDI_TOTAL_FUEL_CONSUMPTION	148	 // 148 - Total Fuel Consumption
#define DDI_INSTANTANEOUS_FUEL_CONSUMPTION_PER_TIME	149	 // 149 - Instantaneous Fuel Consumption per Time
#define DDI_INSTANTANEOUS_FUEL_CONSUMPTION_PER_AREA	150	 // 150 - Instantaneous Fuel Consumption per Area
#define DDI_INSTANTANEOUS_AREA_PER_TIME_CAPACITY	151	 // 151 - Instantaneous Area Per Time Capacity
#define DDI_ACTUAL_NORMALIZED_DIFFERENCE_VEGETATIVE_INDEX_NDVI	153	 // 153 - Actual Normalized Difference Vegetative Index (NDVI)
#define DDI_PHYSICAL_OBJECT_LENGTH	154	 // 154 - Physical Object Length
#define DDI_PHYSICAL_OBJECT_WIDTH	155	 // 155 - Physical Object Width
#define DDI_PHYSICAL_OBJECT_HEIGHT	156	 // 156 - Physical Object Height
#define DDI_CONNECTOR_TYPE	157	 // 157 - Connector Type
#define DDI_PRESCRIPTION_CONTROL_STATE	158	 // 158 - Prescription Control State
#define DDI_NUMBER_OF_SUB_UNITS_PER_SECTION	159	 // 159 - Number of Sub-Units per Section
#define DDI_SECTION_CONTROL_STATE	160	 // 160 - Section Control State
#define DDI_ACTUAL_CONDENSED_WORK_STATE_1_16 161          // 161 - Actual Condensed Work State (1-16)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_17_32 162          // 162 - Actual Condensed Work State (17-32)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_33_48 163          // 163 - Actual Condensed Work State (33-48)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_49_64 164          // 164 - Actual Condensed Work State (49-64)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_65_80 165          // 165 - Actual Condensed Work State (65-80)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_81_96 166          // 166 - Actual Condensed Work State (81-96)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_97_112 167          // 167 - Actual Condensed Work State (97-112)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_113_128 168          // 168 - Actual Condensed Work State (113-128)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_129_144 169          // 169 - Actual Condensed Work State (129-144)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_145_160 170          // 170 - Actual Condensed Work State (145-160)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_161_176 171          // 171 - Actual Condensed Work State (161-176)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_177_192 172          // 172 - Actual Condensed Work State (177-192)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_193_208 173          // 173 - Actual Condensed Work State (193-208)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_209_224 174          // 174 - Actual Condensed Work State (209-224)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_225_240 175          // 175 - Actual Condensed Work State (225-240)
#define DDI_ACTUAL_CONDENSED_WORK_STATE_241_256 176          // 176 - Actual Condensed Work State (241-256)
#define DDI_ACTUAL_LENGTH_OF_CUT	177	 // 177 - Actual length of cut
#define DDI_ELEMENT_TYPE_INSTANCE	178	 // 178 - Element Type Instance
#define DDI_ACTUAL_CULTURAL_PRACTICE	179	 // 179 - Actual Cultural Practice
#define DDI_DEVICE_REFERENCE_POINT_DRP_TO_GROUND_DISTANCE	180	 // 180 - Device Reference Point (DRP) to Ground distance
#define DDI_DRY_MASS_PER_AREA_YIELD	181	 // 181 - Dry Mass Per Area Yield
#define DDI_DRY_MASS_PER_TIME_YIELD	182	 // 182 - Dry Mass Per Time Yield
#define DDI_YIELD_TOTAL_DRY_MASS	183	 // 183 - Yield Total Dry Mass
#define DDI_REFERENCE_MOISTURE_FOR_DRY_MASS	184	 // 184 - Reference Moisture For Dry Mass
#define DDI_SEED_COTTON_MASS_PER_AREA_YIELD	185	 // 185 - Seed Cotton Mass Per Area Yield
#define DDI_LINT_COTTON_MASS_PER_AREA_YIELD	186	 // 186 - Lint Cotton Mass Per Area Yield
#define DDI_SEED_COTTON_MASS_PER_TIME_YIELD	187	 // 187 - Seed Cotton Mass Per Time Yield
#define DDI_LINT_COTTON_MASS_PER_TIME_YIELD	188	 // 188 - Lint Cotton Mass Per Time Yield
#define DDI_YIELD_TOTAL_SEED_COTTON_MASS	189	 // 189 - Yield Total Seed Cotton Mass
#define DDI_YIELD_TOTAL_LINT_COTTON_MASS	190	 // 190 - Yield Total Lint Cotton Mass
#define DDI_LINT_TURNOUT_PERCENTAGE	191	 // 191 - Lint Turnout Percentage
#define DDI_AMBIENT_TEMPERATURE	192	 // 192 - Ambient temperature
#define DDI_SETPOINT_PRODUCT_PRESSURE	193	 // 193 - Setpoint Product Pressure
#define DDI_ACTUAL_PRODUCT_PRESSURE	194	 // 194 - Actual Product Pressure
#define DDI_MINIMUM_PRODUCT_PRESSURE	195	 // 195 - Minimum Product Pressure
#define DDI_MAXIMUM_PRODUCT_PRESSURE	196	 // 196 - Maximum Product Pressure
#define DDI_SETPOINT_PUMP_OUTPUT_PRESSURE	197	 // 197 - Setpoint Pump Output Pressure
#define DDI_ACTUAL_PUMP_OUTPUT_PRESSURE	198	 // 198 - Actual Pump Output Pressure
#define DDI_MINIMUM_PUMP_OUTPUT_PRESSURE	199	 // 199 - Minimum Pump Output Pressure
#define DDI_MAXIMUM_PUMP_OUTPUT_PRESSURE	200	 // 200 - Maximum Pump Output Pressure
#define DDI_SETPOINT_TANK_AGITATION_PRESSURE	201	 // 201 - Setpoint Tank Agitation Pressure
#define DDI_ACTUAL_TANK_AGITATION_PRESSURE	202	 // 202 - Actual Tank Agitation Pressure
#define DDI_MINIMUM_TANK_AGITATION_PRESSURE	203	 // 203 - Minimum Tank Agitation Pressure
#define DDI_MAXIMUM_TANK_AGITATION_PRESSURE	204	 // 204 - Maximum Tank Agitation Pressure
#define DDI_SC_TURN_ON_TIME	205	 // 205 - SC Turn On Time
#define DDI_SC_TURN_OFF_TIME	206	 // 206 - SC Turn Off Time
#define DDI_WIND_SPEED	207	 // 207 - Wind speed
#define DDI_WIND_DIRECTION	208	 // 208 - Wind direction
#define DDI_RELATIVE_HUMIDITY	209	 // 209 - Relative Humidity
#define DDI_SKY_CONDITIONS	210	 // 210 - Sky conditions
#define DDI_LAST_BALE_FLAKES_PER_BALE	211	 // 211 - Last Bale Flakes per Bale
#define DDI_LAST_BALE_AVERAGE_MOISTURE	212	 // 212 - Last Bale Average Moisture
#define DDI_LAST_BALE_AVERAGE_STROKES_PER_FLAKE	213	 // 213 - Last Bale Average Strokes per Flake
#define DDI_LIFETIME_BALE_COUNT	214	 // 214 - Lifetime Bale Count
#define DDI_LIFETIME_WORKING_HOURS	215	 // 215 - Lifetime Working Hours
#define DDI_ACTUAL_BALE_HYDRAULIC_PRESSURE	216	 // 216 - Actual Bale Hydraulic Pressure
#define DDI_LAST_BALE_AVERAGE_HYDRAULIC_PRESSURE	217	 // 217 - Last Bale Average Hydraulic Pressure
#define DDI_SETPOINT_BALE_COMPRESSION_PLUNGER_LOAD	218	 // 218 - Setpoint Bale Compression Plunger Load
#define DDI_ACTUAL_BALE_COMPRESSION_PLUNGER_LOAD	219	 // 219 - Actual Bale Compression Plunger Load
#define DDI_LAST_BALE_AVERAGE_BALE_COMPRESSION_PLUNGER_LOAD	220	 // 220 - Last Bale Average Bale Compression Plunger Load
#define DDI_LAST_BALE_APPLIED_PRESERVATIVE	221	 // 221 - Last Bale Applied Preservative
#define DDI_LAST_BALE_TAG_NUMBER	222	 // 222 - Last Bale Tag Number
#define DDI_LAST_BALE_MASS	223	 // 223 - Last Bale Mass
#define DDI_DELTA_T	224	 // 224 - Delta T
#define DDI_SETPOINT_WORKING_LENGTH	225	 // 225 - Setpoint Working Length
#define DDI_ACTUAL_WORKING_LENGTH	226	 // 226 - Actual Working Length
#define DDI_MINIMUM_WORKING_LENGTH	227	 // 227 - Minimum Working Length
#define DDI_MAXIMUM_WORKING_LENGTH	228	 // 228 - Maximum Working Length
#define DDI_ACTUAL_NET_WEIGHT	229	 // 229 - Actual Net Weight
#define DDI_NET_WEIGHT_STATE	230	 // 230 - Net Weight State
#define DDI_SETPOINT_NET_WEIGHT	231	 // 231 - Setpoint Net Weight
#define DDI_ACTUAL_GROSS_WEIGHT	232	 // 232 - Actual Gross Weight
#define DDI_GROSS_WEIGHT_STATE	233	 // 233 - Gross Weight State
#define DDI_MINIMUM_GROSS_WEIGHT	234	 // 234 - Minimum Gross Weight
#define DDI_MAXIMUM_GROSS_WEIGHT	235	 // 235 - Maximum Gross Weight
#define DDI_THRESHER_ENGAGEMENT_TOTAL_TIME	236	 // 236 - Thresher Engagement Total Time
#define DDI_ACTUAL_HEADER_WORKING_HEIGHT_STATUS	237	 // 237 - Actual Header Working Height Status
#define DDI_ACTUAL_HEADER_ROTATIONAL_SPEED_STATUS	238	 // 238 - Actual Header Rotational Speed Status
#define DDI_YIELD_HOLD_STATUS	239	 // 239 - Yield Hold Status
#define DDI_ACTUAL_UNLOADING_SYSTEM_STATUS	240	 // 240 - Actual (Un)Loading System Status
#define DDI_CROP_TEMPERATURE	241	 // 241 - Crop Temperature
#define DDI_SETPOINT_SIEVE_CLEARANCE	242	 // 242 - Setpoint Sieve Clearance
#define DDI_ACTUAL_SIEVE_CLEARANCE	243	 // 243 - Actual Sieve Clearance
#define DDI_MINIMUM_SIEVE_CLEARANCE	244	 // 244 - Minimum Sieve Clearance
#define DDI_MAXIMUM_SIEVE_CLEARANCE	245	 // 245 - Maximum Sieve Clearance
#define DDI_SETPOINT_CHAFFER_CLEARANCE	246	 // 246 - Setpoint Chaffer Clearance
#define DDI_ACTUAL_CHAFFER_CLEARANCE	247	 // 247 - Actual Chaffer Clearance
#define DDI_MINIMUM_CHAFFER_CLEARANCE	248	 // 248 - Minimum Chaffer Clearance
#define DDI_MAXIMUM_CHAFFER_CLEARANCE	249	 // 249 - Maximum Chaffer Clearance
#define DDI_SETPOINT_CONCAVE_CLEARANCE	250	 // 250 - Setpoint Concave Clearance
#define DDI_ACTUAL_CONCAVE_CLEARANCE	251	 // 251 - Actual Concave Clearance
#define DDI_MINIMUM_CONCAVE_CLEARANCE	252	 // 252 - Minimum Concave Clearance
#define DDI_MAXIMUM_CONCAVE_CLEARANCE	253	 // 253 - Maximum Concave Clearance
#define DDI_SETPOINT_SEPARATION_FAN_ROTATIONAL_SPEED	254	 // 254 - Setpoint Separation Fan Rotational Speed
#define DDI_ACTUAL_SEPARATION_FAN_ROTATIONAL_SPEED	255	 // 255 - Actual Separation Fan Rotational Speed
#define DDI_MINIMUM_SEPARATION_FAN_ROTATIONAL_SPEED	256	 // 256 - Minimum Separation Fan Rotational Speed
#define DDI_MAXIMUM_SEPARATION_FAN_ROTATIONAL_SPEED	257	 // 257 - Maximum Separation Fan Rotational Speed
#define DDI_HYDRAULIC_OIL_TEMPERATURE	258	 // 258 - Hydraulic Oil Temperature
#define DDI_YIELD_LAG_IGNORE_TIME	259	 // 259 - Yield Lag Ignore Time
#define DDI_YIELD_LEAD_IGNORE_TIME	260	 // 260 - Yield Lead Ignore Time
#define DDI_AVERAGE_YIELD_MASS_PER_TIME	261	 // 261 - Average Yield Mass Per Time
#define DDI_AVERAGE_CROP_MOISTURE	262	 // 262 - Average Crop Moisture
#define DDI_AVERAGE_YIELD_MASS_PER_AREA	263	 // 263 - Average Yield Mass Per Area
#define DDI_CONNECTOR_PIVOT_X_OFFSET 264          // 264 - Connector Pivot X-Offset
#define DDI_REMAINING_AREA	265	 // 265 - Remaining Area
#define DDI_LIFETIME_APPLICATION_TOTAL_MASS	266	 // 266 - Lifetime Application Total Mass
#define DDI_LIFETIME_APPLICATION_TOTAL_COUNT	267	 // 267 - Lifetime Application Total Count
#define DDI_LIFETIME_YIELD_TOTAL_VOLUME	268	 // 268 - Lifetime Yield Total Volume
#define DDI_LIFETIME_YIELD_TOTAL_MASS	269	 // 269 - Lifetime Yield Total Mass
#define DDI_LIFETIME_YIELD_TOTAL_COUNT	270	 // 270 - Lifetime Yield Total Count
#define DDI_LIFETIME_TOTAL_AREA	271	 // 271 - Lifetime Total Area
#define DDI_LIFETIME_EFFECTIVE_TOTAL_DISTANCE	272	 // 272 - Lifetime Effective Total Distance
#define DDI_LIFETIME_INEFFECTIVE_TOTAL_DISTANCE	273	 // 273 - Lifetime Ineffective Total Distance
#define DDI_LIFETIME_EFFECTIVE_TOTAL_TIME	274	 // 274 - Lifetime Effective Total Time
#define DDI_LIFETIME_INEFFECTIVE_TOTAL_TIME	275	 // 275 - Lifetime Ineffective Total Time
#define DDI_LIFETIME_FUEL_CONSUMPTION	276	 // 276 - Lifetime Fuel Consumption
#define DDI_LIFETIME_AVERAGE_FUEL_CONSUMPTION_PER_TIME	277	 // 277 - Lifetime Average Fuel Consumption per Time
#define DDI_LIFETIME_AVERAGE_FUEL_CONSUMPTION_PER_AREA	278	 // 278 - Lifetime Average Fuel Consumption per Area
#define DDI_LIFETIME_YIELD_TOTAL_DRY_MASS	279	 // 279 - Lifetime Yield Total Dry Mass
#define DDI_LIFETIME_YIELD_TOTAL_SEED_COTTON_MASS	280	 // 280 - Lifetime Yield Total Seed Cotton Mass
#define DDI_LIFETIME_YIELD_TOTAL_LINT_COTTON_MASS	281	 // 281 - Lifetime Yield Total Lint Cotton Mass
#define DDI_LIFETIME_THRESHING_ENGAGEMENT_TOTAL_TIME	282	 // 282 - Lifetime Threshing Engagement Total Time
#define DDI_PRECUT_TOTAL_COUNT	283	 // 283 - Precut Total Count
#define DDI_UNCUT_TOTAL_COUNT	284	 // 284 - Uncut Total Count
#define DDI_LIFETIME_PRECUT_TOTAL_COUNT	285	 // 285 - Lifetime Precut Total Count
#define DDI_LIFETIME_UNCUT_TOTAL_COUNT	286	 // 286 - Lifetime Uncut Total Count
#define DDI_SETPOINT_PRESCRIPTION_MODE	287	 // 287 - Setpoint Prescription Mode
#define DDI_ACTUAL_PRESCRIPTION_MODE	288	 // 288 - Actual Prescription Mode
#define DDI_SETPOINT_WORK_STATE	289	 // 289 - Setpoint Work State
#define DDI_SETPOINT_CONDENSED_WORK_STATE_1_16 290          // 290 - Setpoint Condensed Work State (1-16)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_17_32 291          // 291 - Setpoint Condensed Work State (17-32)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_33_48 292          // 292 - Setpoint Condensed Work State (33-48)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_49_64 293          // 293 - Setpoint Condensed Work State (49-64)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_65_80 294          // 294 - Setpoint Condensed Work State (65-80)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_81_96 295          // 295 - Setpoint Condensed Work State (81-96)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_97_112 296          // 296 - Setpoint Condensed Work State (97-112)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_113_128 297          // 297 - Setpoint Condensed Work State (113-128)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_129_144 298          // 298 - Setpoint Condensed Work State (129-144)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_145_160 299          // 299 - Setpoint Condensed Work State (145-160)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_161_176 300          // 300 - Setpoint Condensed Work State (161-176)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_177_192 301          // 301 - Setpoint Condensed Work State (177-192)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_193_208 302          // 302 - Setpoint Condensed Work State (193-208)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_209_224 303          // 303 - Setpoint Condensed Work State (209-224)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_225_240 304          // 304 - Setpoint Condensed Work State (225-240)
#define DDI_SETPOINT_CONDENSED_WORK_STATE_241_256 305          // 305 - Setpoint Condensed Work State (241-256)
#define DDI_TRUE_ROTATION_POINT_X_OFFSET 306          // 306 - True Rotation Point  X-Offset
#define DDI_TRUE_ROTATION_POINT_Y_OFFSET 307          // 307 - True Rotation Point Y-Offset
#define DDI_ACTUAL_PERCENTAGE_APPLICATION_RATE	308	 // 308 - Actual Percentage Application Rate
#define DDI_MINIMUM_PERCENTAGE_APPLICATION_RATE	309	 // 309 - Minimum Percentage Application Rate
#define DDI_MAXIMUM_PERCENTAGE_APPLICATION_RATE	310	 // 310 - Maximum Percentage Application Rate
#define DDI_RELATIVE_YIELD_POTENTIAL	311	 // 311 - Relative Yield Potential
#define DDI_MINIMUM_RELATIVE_YIELD_POTENTIAL	312	 // 312 - Minimum Relative Yield Potential
#define DDI_MAXIMUM_RELATIVE_YIELD_POTENTIAL	313	 // 313 - Maximum Relative Yield Potential
#define DDI_ACTUAL_PERCENTAGE_CROP_DRY_MATTER	314	 // 314 - Actual Percentage Crop Dry Matter
#define DDI_AVERAGE_PERCENTAGE_CROP_DRY_MATTER	315	 // 315 - Average Percentage Crop Dry Matter
#define DDI_EFFECTIVE_TOTAL_FUEL_CONSUMPTION	316	 // 316 - Effective Total Fuel Consumption
#define DDI_INEFFECTIVE_TOTAL_FUEL_CONSUMPTION	317	 // 317 - Ineffective Total Fuel Consumption
#define DDI_EFFECTIVE_TOTAL_DIESEL_EXHAUST_FLUID_CONSUMPTION	318	 // 318 - Effective Total Diesel Exhaust Fluid Consumption
#define DDI_INEFFECTIVE_TOTAL_DIESEL_EXHAUST_FLUID_CONSUMPTION	319	 // 319 - Ineffective Total Diesel Exhaust Fluid Consumption
#define DDI_LAST_LOADED_WEIGHT	320	 // 320 - Last loaded Weight
#define DDI_LAST_UNLOADED_WEIGHT	321	 // 321 - Last unloaded Weight
#define DDI_LOAD_IDENTIFICATION_NUMBER	322	 // 322 - Load Identification Number
#define DDI_UNLOAD_IDENTIFICATION_NUMBER	323	 // 323 - Unload Identification Number
#define DDI_CHOPPER_ENGAGEMENT_TOTAL_TIME	324	 // 324 - Chopper Engagement Total Time
#define DDI_LIFETIME_APPLICATION_TOTAL_VOLUME	325	 // 325 - Lifetime Application Total Volume
#define DDI_SETPOINT_HEADER_SPEED	326	 // 326 - Setpoint Header Speed
#define DDI_ACTUAL_HEADER_SPEED	327	 // 327 - Actual Header Speed
#define DDI_MINIMUM_HEADER_SPEED	328	 // 328 - Minimum Header Speed
#define DDI_MAXIMUM_HEADER_SPEED	329	 // 329 - Maximum Header Speed
#define DDI_SETPOINT_CUTTING_DRUM_SPEED	330	 // 330 - Setpoint Cutting drum speed
#define DDI_ACTUAL_CUTTING_DRUM_SPEED	331	 // 331 - Actual Cutting drum speed
#define DDI_MINIMUM_CUTTING_DRUM_SPEED	332	 // 332 - Minimum Cutting drum speed
#define DDI_MAXIMUM_CUTTING_DRUM_SPEED	333	 // 333 - Maximum Cutting drum speed
#define DDI_OPERATING_HOURS_SINCE_LAST_SHARPENING	334	 // 334 - Operating Hours Since Last Sharpening
#define DDI_FRONT_PTO_HOURS	335	 // 335 - Front PTO hours
#define DDI_REAR_PTO_HOURS	336	 // 336 - Rear PTO hours
#define DDI_LIFETIME_FRONT_PTO_HOURS	337	 // 337 - Lifetime Front PTO hours
#define DDI_LIFETIME_REAR_PTO_HOURS	338	 // 338 - Lifetime Rear PTO Hours
#define DDI_EFFECTIVE_TOTAL_LOADING_TIME	339	 // 339 - Effective Total Loading Time
#define DDI_EFFECTIVE_TOTAL_UNLOADING_TIME	340	 // 340 - Effective Total Unloading Time
#define DDI_SETPOINT_GRAIN_KERNEL_CRACKER_GAP	341	 // 341 - Setpoint Grain Kernel Cracker Gap
#define DDI_ACTUAL_GRAIN_KERNEL_CRACKER_GAP	342	 // 342 - Actual Grain Kernel Cracker Gap
#define DDI_MINIMUM_GRAIN_KERNEL_CRACKER_GAP	343	 // 343 - Minimum Grain Kernel Cracker Gap
#define DDI_MAXIMUM_GRAIN_KERNEL_CRACKER_GAP	344	 // 344 - Maximum Grain Kernel Cracker Gap
#define DDI_SETPOINT_SWATHING_WIDTH	345	 // 345 - Setpoint Swathing Width
#define DDI_ACTUAL_SWATHING_WIDTH	346	 // 346 - Actual Swathing Width
#define DDI_MINIMUM_SWATHING_WIDTH	347	 // 347 - Minimum Swathing Width
#define DDI_MAXIMUM_SWATHING_WIDTH	348	 // 348 - Maximum Swathing Width
#define DDI_NOZZLE_DRIFT_REDUCTION	349	 // 349 - Nozzle Drift Reduction
#define DDI_FUNCTION_OR_OPERATION_TECHNIQUE	350	 // 350 - Function or Operation Technique
#define DDI_APPLICATION_TOTAL_VOLUME_IN_ML	351	 // 351 - Application Total Volume in [ml]
#define DDI_APPLICATION_TOTAL_MASS_IN_GRAM_G	352	 // 352 - Application Total Mass in gram [g]
#define DDI_TOTAL_APPLICATION_OF_NITROGEN	353	 // 353 - Total Application of Nitrogen
#define DDI_TOTAL_APPLICATION_OF_AMMONIUM	354	 // 354 - Total Application of Ammonium
#define DDI_TOTAL_APPLICATION_OF_PHOSPHOR	355	 // 355 - Total Application of Phosphor
#define DDI_TOTAL_APPLICATION_OF_POTASSIUM	356	 // 356 - Total Application of Potassium
#define DDI_TOTAL_APPLICATION_OF_DRY_MATTER	357	 // 357 - Total Application of Dry Matter
#define DDI_AVERAGE_DRY_YIELD_MASS_PER_TIME	358	 // 358 - Average Dry Yield Mass Per Time
#define DDI_AVERAGE_DRY_YIELD_MASS_PER_AREA	359	 // 359 - Average Dry Yield Mass Per Area
#define DDI_LAST_BALE_SIZE	360	 // 360 - Last Bale Size
#define DDI_LAST_BALE_DENSITY	361	 // 361 - Last Bale Density
#define DDI_TOTAL_BALE_LENGTH	362	 // 362 - Total Bale Length
#define DDI_LAST_BALE_DRY_MASS	363	 // 363 - Last Bale Dry Mass
#define DDI_ACTUAL_FLAKE_SIZE	364	 // 364 - Actual Flake Size
#define DDI_SETPOINT_DOWNFORCE_PRESSURE	365	 // 365 - Setpoint Downforce Pressure
#define DDI_ACTUAL_DOWNFORCE_PRESSURE	366	 // 366 - Actual Downforce Pressure
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_1_16 367          // 367 - Condensed Section Override State (1-16)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_17_32 368          // 368 - Condensed Section Override State (17-32)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_33_48 369          // 369 - Condensed Section Override State (33-48)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_49_64 370          // 370 - Condensed Section Override State (49-64)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_65_80 371          // 371 - Condensed Section Override State (65-80)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_81_96 372          // 372 - Condensed Section Override State (81-96)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_97_112 373          // 373 - Condensed Section Override State (97-112)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_113_128 374          // 374 - Condensed Section Override State (113-128)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_129_144 375          // 375 - Condensed Section Override State (129-144)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_145_160 376          // 376 - Condensed Section Override State (145-160)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_161_176 377          // 377 - Condensed Section Override State (161-176)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_177_192 378          // 378 - Condensed Section Override State (177-192)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_193_208 379          // 379 - Condensed Section Override State (193-208)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_209_224 380          // 380 - Condensed Section Override State (209-224)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_225_240 381          // 381 - Condensed Section Override State (225-240)
#define DDI_CONDENSED_SECTION_OVERRIDE_STATE_241_256 382          // 382 - Condensed Section Override State (241-256)
#define DDI_APPARENT_WIND_DIRECTION	383	 // 383 - Apparent Wind Direction
#define DDI_APPARENT_WIND_SPEED	384	 // 384 - Apparent Wind Speed
#define DDI_MSL_ATMOSPHERIC_PRESSURE	385	 // 385 - MSL Atmospheric Pressure
#define DDI_ACTUAL_ATMOSPHERIC_PRESSURE	386	 // 386 - Actual Atmospheric Pressure
#define DDI_TOTAL_REVOLUTIONS_IN_FRACTIONAL_REVOLUTIONS	387	 // 387 - Total Revolutions in Fractional Revolutions
#define DDI_TOTAL_REVOLUTIONS_IN_COMPLETE_REVOLUTIONS	388	 // 388 - Total Revolutions in Complete Revolutions
#define DDI_SETPOINT_REVOLUTIONS_SPECIFIED_AS_COUNT_PER_TIME	389	 // 389 - Setpoint Revolutions specified as count per time
#define DDI_ACTUAL_REVOLUTIONS_PER_TIME	390	 // 390 - Actual Revolutions Per Time
#define DDI_DEFAULT_REVOLUTIONS_PER_TIME	391	 // 391 - Default Revolutions Per Time
#define DDI_MINIMUM_REVOLUTIONS_PER_TIME	392	 // 392 - Minimum Revolutions Per Time
#define DDI_MAXIMUM_REVOLUTIONS_PER_TIME	393	 // 393 - Maximum Revolutions Per Time
#define DDI_ACTUAL_FUEL_TANK_CONTENT	394	 // 394 - Actual Fuel Tank Content
#define DDI_ACTUAL_DIESEL_EXHAUST_FLUID_TANK_CONTENT	395	 // 395 - Actual Diesel Exhaust Fluid Tank Content
#define DDI_SETPOINT_SPEED	396	 // 396 - Setpoint Speed
#define DDI_ACTUAL_SPEED	397	 // 397 - Actual Speed
#define DDI_MINIMUM_SPEED	398	 // 398 - Minimum Speed
#define DDI_MAXIMUM_SPEED	399	 // 399 - Maximum Speed
#define DDI_SPEED_SOURCE	400	 // 400 - Speed Source
#define DDI_ACTUAL_APPLICATION_OF_NITROGEN	401	 // 401 - Actual Application of Nitrogen
#define DDI_ACTUAL_APPLICATION_OF_AMMONIUM	402	 // 402 - Actual application of Ammonium
#define DDI_ACTUAL_APPLICATION_OF_PHOSPHOR	403	 // 403 - Actual application of Phosphor
#define DDI_ACTUAL_APPLICATION_OF_POTASSIUM	404	 // 404 - Actual application of Potassium
#define DDI_ACTUAL_APPLICATION_OF_DRY_MATTER	405	 // 405 - Actual application of Dry Matter
#define DDI_ACTUAL_PROTEIN_CONTENT	406	 // 406 - Actual Protein Content
#define DDI_AVERAGE_PROTEIN_CONTENT	407	 // 407 - Average Protein Content
#define DDI_AVERAGE_CROP_CONTAMINATION	408	 // 408 - Average Crop Contamination
#define DDI_TOTAL_DIESEL_EXHAUST_FLUID_CONSUMPTION	409	 // 409 - Total Diesel Exhaust Fluid Consumption
#define DDI_INSTANTANEOUS_DIESEL_EXHAUST_FLUID_CONSUMPTION_PER_TIME	410	 // 410 - Instantaneous Diesel Exhaust Fluid Consumption per Time
#define DDI_INSTANTANEOUS_DIESEL_EXHAUST_FLUID_CONSUMPTION_PER_AREA	411	 // 411 - Instantaneous Diesel Exhaust Fluid Consumption per Area
#define DDI_LIFETIME_DIESEL_EXHAUST_FLUID_CONSUMPTION	412	 // 412 - Lifetime Diesel Exhaust Fluid Consumption
#define DDI_LIFETIME_AVERAGE_DIESEL_EXHAUST_FLUID_CONSUMPTION_PER_TIME	413	 // 413 - Lifetime Average Diesel Exhaust Fluid Consumption per Time
#define DDI_LIFETIME_AVERAGE_DIESEL_EXHAUST_FLUID_CONSUMPTION_PER_AREA	414	 // 414 - Lifetime Average Diesel Exhaust Fluid Consumption per Area
#define DDI_ACTUAL_SEED_SINGULATION_PERCENTAGE	415	 // 415 - Actual Seed Singulation Percentage
#define DDI_AVERAGE_SEED_SINGULATION_PERCENTAGE	416	 // 416 - Average Seed Singulation Percentage
#define DDI_ACTUAL_SEED_SKIP_PERCENTAGE	417	 // 417 - Actual Seed Skip Percentage
#define DDI_AVERAGE_SEED_SKIP_PERCENTAGE	418	 // 418 - Average Seed Skip Percentage
#define DDI_ACTUAL_SEED_MULTIPLE_PERCENTAGE	419	 // 419 - Actual Seed Multiple Percentage
#define DDI_AVERAGE_SEED_MULTIPLE_PERCENTAGE	420	 // 420 - Average Seed Multiple Percentage
#define DDI_ACTUAL_SEED_SPACING_DEVIATION	421	 // 421 - Actual Seed Spacing Deviation
#define DDI_AVERAGE_SEED_SPACING_DEVIATION	422	 // 422 - Average Seed Spacing Deviation
#define DDI_ACTUAL_COEFFICIENT_OF_VARIATION_OF_SEED_SPACING_PERCENTAGE	423	 // 423 - Actual Coefficient of Variation of Seed Spacing Percentage
#define DDI_AVERAGE_COEFFICIENT_OF_VARIATION_OF_SEED_SPACING_PERCENTAGE	424	 // 424 - Average Coefficient of Variation of Seed Spacing Percentage
#define DDI_SETPOINT_MAXIMUM_ALLOWED_SEED_SPACING_DEVIATION	425	 // 425 - Setpoint Maximum Allowed Seed Spacing Deviation
#define DDI_SETPOINT_DOWNFORCE_AS_FORCE	426	 // 426 - Setpoint Downforce as Force
#define DDI_ACTUAL_DOWNFORCE_AS_FORCE	427	 // 427 - Actual Downforce as Force
#define DDI_LOADED_TOTAL_MASS	428	 // 428 - Loaded Total Mass
#define DDI_UNLOADED_TOTAL_MASS	429	 // 429 - Unloaded Total Mass
#define DDI_LIFETIME_LOADED_TOTAL_MASS	430	 // 430 - Lifetime Loaded Total Mass
#define DDI_LIFETIME_UNLOADED_TOTAL_MASS	431	 // 431 - Lifetime Unloaded Total Mass
#define DDI_SETPOINT_APPLICATION_RATE_OF_NITROGEN	432	 // 432 - Setpoint Application Rate of Nitrogen
#define DDI_ACTUAL_APPLICATION_RATE_OF_NITROGEN	433	 // 433 - Actual  Application Rate of Nitrogen
#define DDI_MINIMUM_APPLICATION_RATE_OF_NITROGEN	434	 // 434 - Minimum Application Rate of Nitrogen
#define DDI_MAXIMUM_APPLICATION_RATE_OF_NITROGEN	435	 // 435 - Maximum  Application Rate of Nitrogen
#define DDI_SETPOINT_APPLICATION_RATE_OF_AMMONIUM	436	 // 436 - Setpoint  Application Rate of Ammonium
#define DDI_ACTUAL_APPLICATION_RATE_OF_AMMONIUM	437	 // 437 - Actual  Application Rate of Ammonium
#define DDI_MINIMUM_APPLICATION_RATE_OF_AMMONIUM	438	 // 438 - Minimum  Application Rate of Ammonium
#define DDI_MAXIMUM_APPLICATION_RATE_OF_AMMONIUM	439	 // 439 - Maximum  Application Rate of Ammonium
#define DDI_SETPOINT_APPLICATION_RATE_OF_PHOSPHOR	440	 // 440 - Setpoint  Application Rate of Phosphor
#define DDI_ACTUAL_APPLICATION_RATE_OF_PHOSPHOR	441	 // 441 - Actual  Application Rate of Phosphor
#define DDI_MINIMUM_APPLICATION_RATE_OF_PHOSPHOR	442	 // 442 - Minimum  Application Rate of Phosphor
#define DDI_MAXIMUM_APPLICATION_RATE_OF_PHOSPHOR	443	 // 443 - Maximum  Application Rate of Phosphor
#define DDI_SETPOINT_APPLICATION_RATE_OF_POTASSIUM	444	 // 444 - Setpoint  Application Rate of Potassium
#define DDI_ACTUAL_APPLICATION_RATE_OF_POTASSIUM	445	 // 445 - Actual  Application Rate of Potassium
#define DDI_MINIMUM_APPLICATION_RATE_OF_POTASSIUM	446	 // 446 - Minimum Application Rate of Potassium
#define DDI_MAXIMUM_APPLICATION_RATE_OF_POTASSIUM	447	 // 447 - Maximum Application Rate of Potassium
#define DDI_SETPOINT_APPLICATION_RATE_OF_DRY_MATTER	448	 // 448 - Setpoint Application Rate of Dry Matter
#define DDI_ACTUAL_APPLICATION_RATE_OF_DRY_MATTER	449	 // 449 - Actual  Application Rate of Dry Matter
#define DDI_MINIMUM_APPLICATION_RATE_OF_DRY_MATTER	450	 // 450 - Minimum Application Rate of Dry Matter
#define DDI_MAXIMUM_APPLICATION_RATE_OF_DRY_MATTER	451	 // 451 - Maximum Application Rate of Dry Matter
#define DDI_LOADED_TOTAL_VOLUME	452	 // 452 - Loaded Total Volume
#define DDI_UNLOADED_TOTAL_VOLUME	453	 // 453 - Unloaded Total Volume
#define DDI_LIFETIME_LOADED_TOTAL_VOLUME	454	 // 454 - Lifetime loaded Total Volume
#define DDI_LIFETIME_UNLOADED_TOTAL_VOLUME	455	 // 455 - Lifetime Unloaded Total Volume
#define DDI_LAST_LOADED_VOLUME	456	 // 456 - Last loaded Volume
#define DDI_LAST_UNLOADED_VOLUME	457	 // 457 - Last unloaded Volume
#define DDI_LOADED_TOTAL_COUNT	458	 // 458 - Loaded Total Count
#define DDI_UNLOADED_TOTAL_COUNT	459	 // 459 - Unloaded Total Count
#define DDI_LIFETIME_LOADED_TOTAL_COUNT	460	 // 460 - Lifetime Loaded Total Count
#define DDI_LIFETIME_UNLOADED_TOTAL_COUNT	461	 // 461 - Lifetime Unloaded Total Count
#define DDI_LAST_LOADED_COUNT	462	 // 462 - Last loaded Count
#define DDI_LAST_UNLOADED_COUNT	463	 // 463 - Last unloaded Count
#define DDI_HAUL_COUNTER	464	 // 464 - Haul Counter
#define DDI_LIFETIME_HAUL_COUNTER	465	 // 465 - Lifetime Haul Counter
#define DDI_ACTUAL_RELATIVE_CONNECTOR_ANGLE	466	 // 466 - Actual relative connector angle
#define DDI_ACTUAL_PERCENTAGE_CONTENT	467	 // 467 - Actual Percentage Content
#define DDI_SOIL_SNOW_FROZEN_CONDTION	468	 // 468 - Soil Snow/Frozen Condtion
#define DDI_ESTIMATED_SOIL_WATER_CONDTION	469	 // 469 - Estimated Soil Water Condtion
#define DDI_SOIL_COMPACTION	470	 // 470 - Soil Compaction
#define DDI_SETPOINT_LENGTH_OF_CUT	472	 // 472 - Setpoint Length of Cut
#define DDI_MINIMUM_LENGTH_OF_CUT	473	 // 473 - Minimum length of cut
#define DDI_MAXIMUM_LENGTH_OF_CUT	474	 // 474 - Maximum Length of Cut
#define DDI_SETPOINT_BALE_HYDRAULIC_PRESSURE	475	 // 475 - Setpoint Bale Hydraulic Pressure
#define DDI_MINIMUM_BALE_HYDRAULIC_PRESSURE	476	 // 476 - Minimum Bale Hydraulic Pressure
#define DDI_MAXIMUM_BALE_HYDRAULIC_PRESSURE	477	 // 477 - Maximum Bale Hydraulic Pressure
#define DDI_SETPOINT_FLAKE_SIZE	478	 // 478 - Setpoint Flake Size
#define DDI_MINIMUM_FLAKE_SIZE	479	 // 479 - Minimum Flake Size
#define DDI_MAXIMUM_FLAKE_SIZE	480	 // 480 - Maximum Flake Size
#define DDI_SETPOINT_NUMBER_OF_SUBBALES	481	 // 481 - Setpoint Number of Subbales
#define DDI_LAST_BALE_NUMBER_OF_SUBBALES	482	 // 482 - Last Bale Number of Subbales
#define DDI_SETPOINT_ENGINE_SPEED	483	 // 483 - Setpoint Engine Speed
#define DDI_ACTUAL_ENGINE_SPEED	484	 // 484 - Actual Engine Speed
#define DDI_MINIMUM_ENGINE_SPEED	485	 // 485 - Minimum Engine Speed
#define DDI_MAXIMUM_ENGINE_SPEED	486	 // 486 - Maximum Engine Speed
#define DDI_DIESEL_EXHAUST_FLUID_TANK_PERCENTAGE_LEVEL	488	 // 488 - Diesel Exhaust Fluid Tank Percentage Level
#define DDI_MAXIMUM_DIESEL_EXHAUST_FLUID_TANK_CONTENT	489	 // 489 - Maximum Diesel Exhaust Fluid Tank Content
#define DDI_MAXIMUM_FUEL_TANK_CONTENT	490	 // 490 - Maximum Fuel Tank Content
#define DDI_FUEL_PERCENTAGE_LEVEL	491	 // 491 - Fuel Percentage Level
#define DDI_TOTAL_ENGINE_HOURS	492	 // 492 - Total Engine Hours
#define DDI_LIFETIME_ENGINE_HOURS	493	 // 493 - Lifetime Engine Hours
#define DDI_LAST_EVENT_PARTNER_ID_BYTE_1_4 494          // 494 - Last Event Partner ID (Byte 1-4)
#define DDI_LAST_EVENT_PARTNER_ID_BYTE_5_8 495          // 495 - Last Event Partner ID (Byte 5-8)
#define DDI_LAST_EVENT_PARTNER_ID_BYTE_9_12 496          // 496 - Last Event Partner ID (Byte 9-12)
#define DDI_LAST_EVENT_PARTNER_ID_BYTE_13_16 497          // 497 - Last Event Partner ID (Byte 13-16)
#define DDI_LAST_EVENT_PARTNER_ID_TYPE	498	 // 498 - Last Event Partner ID Type
#define DDI_LAST_EVENT_PARTNER_ID_MANUFACTURER_ID_CODE	499	 // 499 - Last Event Partner ID Manufacturer ID Code
#define DDI_LAST_EVENT_PARTNER_ID_DEVICE_CLASS	500	 // 500 - Last Event Partner ID Device Class
#define DDI_SETPOINT_ENGINE_TORQUE	501	 // 501 - Setpoint Engine Torque
#define DDI_ACTUAL_ENGINE_TORQUE	502	 // 502 - Actual Engine Torque
#define DDI_MINIMUM_ENGINE_TORQUE	503	 // 503 - Minimum Engine Torque
#define DDI_MAXIMUM_ENGINE_TORQUE	504	 // 504 - Maximum Engine Torque
#define DDI_TRAMLINE_CONTROL_LEVEL	505	 // 505 - Tramline Control Level
#define DDI_SETPOINT_TRAMLINE_CONTROL_LEVEL	506	 // 506 - Setpoint Tramline Control Level
#define DDI_TRAMLINE_SEQUENCE_NUMBER	507	 // 507 - Tramline Sequence Number
#define DDI_UNIQUE_A_B_GUIDANCE_REFERENCE_LINE_ID 508          // 508 - Unique A-B Guidance Reference Line ID
#define DDI_ACTUAL_TRACK_NUMBER	509	 // 509 - Actual Track Number
#define DDI_TRACK_NUMBER_TO_THE_RIGHT	510	 // 510 - Track Number to the right
#define DDI_TRACK_NUMBER_TO_THE_LEFT	511	 // 511 - Track Number to the left
#define DDI_GUIDANCE_LINE_SWATH_WIDTH	512	 // 512 - Guidance Line Swath Width
#define DDI_GUIDANCE_LINE_DEVIATION	513	 // 513 - Guidance Line Deviation
#define DDI_GNSS_QUALITY	514	 // 514 - GNSS Quality
#define DDI_TRAMLINE_CONTROL_STATE	515	 // 515 - Tramline Control State
#define DDI_TRAMLINE_OVERDOSING_RATE	516	 // 516 - Tramline Overdosing Rate
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_1_16 517          // 517 - Setpoint Tramline Condensed Work State 1-16
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_1_16 518          // 518 - Actual Tramline Condensed Work State 1-16
#define DDI_LAST_BALE_LIFETIME_COUNT	519	 // 519 - Last Bale Lifetime Count
#define DDI_ACTUAL_CANOPY_HEIGHT	520	 // 520 - Actual Canopy Height
#define DDI_GNSS_INSTALLATION_TYPE	521	 // 521 - GNSS Installation Type
#define DDI_TWINE_BALE_TOTAL_COUNT	522	 // 522 - Twine Bale Total Count
#define DDI_MESH_BALE_TOTAL_COUNT	523	 // 523 - Mesh Bale Total Count
#define DDI_LIFETIME_TWINE_BALE_TOTAL_COUNT	524	 // 524 - Lifetime Twine Bale Total Count
#define DDI_LIFETIME_MESH_BALE_TOTAL_COUNT	525	 // 525 - Lifetime Mesh Bale Total Count
#define DDI_ACTUAL_COOLING_FLUID_TEMPERATURE	526	 // 526 - Actual Cooling Fluid Temperature
#define DDI_LAST_BALE_CAPACITY	528	 // 528 - Last Bale Capacity
#define DDI_SETPOINT_TILLAGE_DISC_GANG_ANGLE	529	 // 529 - Setpoint Tillage Disc Gang Angle
#define DDI_ACTUAL_TILLAGE_DISC_GANG_ANGLE	530	 // 530 - Actual Tillage Disc Gang Angle
#define DDI_ACTUAL_APPLIED_PRESERVATIVE_PER_YIELD_MASS	531	 // 531 - Actual Applied Preservative Per Yield Mass
#define DDI_SETPOINT_APPLIED_PRESERVATIVE_PER_YIELD_MASS	532	 // 532 - Setpoint Applied Preservative Per Yield Mass
#define DDI_DEFAULT_APPLIED_PRESERVATIVE_PER_YIELD_MASS	533	 // 533 - Default Applied Preservative Per Yield Mass
#define DDI_MINIMUM_APPLIED_PRESERVATIVE_PER_YIELD_MASS	534	 // 534 - Minimum Applied Preservative Per Yield Mass
#define DDI_MAXIMUM_APPLIED_PRESERVATIVE_PER_YIELD_MASS	535	 // 535 - Maximum Applied Preservative Per Yield Mass
#define DDI_TOTAL_APPLIED_PRESERVATIVE	536	 // 536 - Total Applied Preservative
#define DDI_LIFETIME_APPLIED_PRESERVATIVE	537	 // 537 - Lifetime Applied Preservative
#define DDI_AVERAGE_APPLIED_PRESERVATIVE_PER_YIELD_MASS	538	 // 538 - Average Applied Preservative Per Yield Mass
#define DDI_ACTUAL_PRESERVATIVE_TANK_VOLUME	539	 // 539 - Actual Preservative Tank Volume
#define DDI_ACTUAL_PRESERVATIVE_TANK_LEVEL	540	 // 540 - Actual Preservative Tank Level
#define DDI_ACTUAL_PTO_SPEED	541	 // 541 - Actual PTO Speed
#define DDI_SETPOINT_PTO_SPEED	542	 // 542 - Setpoint PTO Speed
#define DDI_DEFAULT_PTO_SPEED	543	 // 543 - Default PTO Speed
#define DDI_MINIMUM_PTO_SPEED	544	 // 544 - Minimum PTO Speed
#define DDI_MAXIMUM_PTO_SPEED	545	 // 545 - Maximum PTO Speed
#define DDI_LIFETIME_CHOPPING_ENGAGEMENT_TOTAL_TIME	546	 // 546 - Lifetime Chopping Engagement Total Time
#define DDI_SETPOINT_BALE_COMPRESSION_PLUNGER_LOAD_(N)	547	 // 547 - Setpoint Bale Compression Plunger Load (N)
#define DDI_ACTUAL_BALE_COMPRESSION_PLUNGER_LOAD_(N)	548	 // 548 - Actual Bale Compression Plunger Load (N)
#define DDI_LAST_BALE_AVERAGE_BALE_COMPRESSION_PLUNGER_LOAD_(N)	549	 // 549 - Last Bale Average Bale Compression Plunger Load (N)
#define DDI_GROUND_COVER	550	 // 550 - Ground Cover
#define DDI_ACTUAL_PTO_TORQUE	551	 // 551 - Actual PTO Torque
#define DDI_SETPOINT_PTO_TORQUE	552	 // 552 - Setpoint PTO Torque
#define DDI_DEFAULT_PTO_TORQUE	553	 // 553 - Default PTO Torque
#define DDI_MINIMUM_PTO_TORQUE	554	 // 554 - Minimum PTO Torque
#define DDI_MAXIMUM_PTO_TORQUE	555	 // 555 - Maximum PTO Torque
#define DDI_PRESENT_WEATHER_CONDITIONS	556	 // 556 - Present Weather Conditions
#define DDI_SETPOINT_ELECTRICAL_CURRENT	557	 // 557 - Setpoint Electrical Current
#define DDI_ACTUAL_ELECTRICAL_CURRENT	558	 // 558 - Actual Electrical Current
#define DDI_MINIMUM_ELECTRICAL_CURRENT	559	 // 559 - Minimum Electrical Current
#define DDI_MAXIMUM_ELECTRICAL_CURRENT	560	 // 560 - Maximum Electrical Current
#define DDI_DEFAULT_ELECTRICAL_CURRENT	561	 // 561 - Default Electrical Current
#define DDI_SETPOINT_VOLTAGE	562	 // 562 - Setpoint Voltage
#define DDI_DEFAULT_VOLTAGE	563	 // 563 - Default Voltage
#define DDI_ACTUAL_VOLTAGE	564	 // 564 - Actual Voltage
#define DDI_MINIMUM_VOLTAGE	565	 // 565 - Minimum Voltage
#define DDI_MAXIMUM_VOLTAGE	566	 // 566 - Maximum Voltage
#define DDI_ACTUAL_ELECTRICAL_RESISTANCE	567	 // 567 - Actual Electrical Resistance
#define DDI_SETPOINT_ELECTRICAL_POWER	568	 // 568 - Setpoint Electrical Power
#define DDI_ACTUAL_ELECTRICAL_POWER	569	 // 569 - Actual Electrical Power
#define DDI_DEFAULT_ELECTRICAL_POWER	570	 // 570 - Default Electrical Power
#define DDI_MAXIMUM_ELECTRICAL_POWER	571	 // 571 - Maximum Electrical Power
#define DDI_MINIMUM_ELECTRICAL_POWER	572	 // 572 - Minimum Electrical Power
#define DDI_TOTAL_ELECTRICAL_ENERGY	573	 // 573 - Total Electrical Energy
#define DDI_SETPOINT_ELECTRICAL_ENERGY_PER_AREA_APPLICATION_RATE	574	 // 574 - Setpoint Electrical Energy per Area Application Rate
#define DDI_ACTUAL_ELECTRICAL_ENERGY_PER_AREA_APPLICATION_RATE	575	 // 575 - Actual  Electrical Energy per Area Application Rate
#define DDI_MAXIMUM_ELECTRICAL_ENERGY_PER_AREA_APPLICATION_RATE	576	 // 576 - Maximum  Electrical Energy  per Area Application Rate
#define DDI_MINIMUM_ELECTRICAL_ENERGY_PER_AREA_APPLICATION_RATE	577	 // 577 - Minimum  Electrical Energy per Area Application Rate
#define DDI_SETPOINT_TEMPERATURE	578	 // 578 - Setpoint Temperature
#define DDI_ACTUAL_TEMPERATURE	579	 // 579 - Actual Temperature
#define DDI_MINIMUM_TEMPERATURE	580	 // 580 - Minimum Temperature
#define DDI_MAXIMUM_TEMPERATURE	581	 // 581 - Maximum Temperature
#define DDI_DEFAULT_TEMPERATURE	582	 // 582 - Default Temperature
#define DDI_SETPOINT_FREQUENCY	583	 // 583 - Setpoint Frequency
#define DDI_ACTUAL_FREQUENCY	584	 // 584 - Actual Frequency
#define DDI_MINIMUM_FREQUENCY	585	 // 585 - Minimum Frequency
#define DDI_MAXIMUM_FREQUENCY	586	 // 586 - Maximum Frequency
#define DDI_PREVIOUS_RAINFALL	587	 // 587 - Previous Rainfall
#define DDI_SETPOINT_VOLUME_PER_AREA_APPLICATION_RATE_BIG	588	 // 588 - Setpoint Volume Per Area Application Rate as [ml/m²]
#define DDI_ACTUAL_VOLUME_PER_AREA_APPLICATION_RATE_BIG	589	 // 589 - Actual Volume Per Area Application Rate as [ml/m²]
#define DDI_MINIMUM_VOLUME_PER_AREA_APPLICATION_RATE_BIG	590	 // 590 - Minimum Volume Per Area Application Rate as [ml/m²]
#define DDI_MAXIMUM_VOLUME_PER_AREA_APPLICATION_RATE_BIG	591	 // 591 - Maximum Volume Per Area Application Rate as [ml/m²]
#define DDI_DEFAULT_VOLUME_PER_AREA_APPLICATION_RATE_BIG	592	 // 592 - Default Volume Per Area Application Rate as [ml/m²]
#define DDI_TRACTION_TYPE	593	 // 593 - Traction Type
#define DDI_MACHINE_MODE	595	 // 595 - Machine Mode
#define DDI_CARGO_AREA_COVER_STATE	596	 // 596 - Cargo Area Cover State
#define DDI_TOTAL_DISTANCE	597	 // 597 - Total Distance
#define DDI_LIFETIME_TOTAL_DISTANCE	598	 // 598 - Lifetime Total Distance
#define DDI_TOTAL_DISTANCE_FIELD	599	 // 599 - Total Distance Field
#define DDI_LIFETIME_TOTAL_DISTANCE_FIELD	600	 // 600 - Lifetime Total Distance Field
#define DDI_TOTAL_DISTANCE_STREET	601	 // 601 - Total Distance Street
#define DDI_LIFETIME_TOTAL_DISTANCE_STREET	602	 // 602 - Lifetime Total Distance Street
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_17_32 	603	 // 603 - Actual Tramline Condensed Work State (17-32)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_33_48 	604	 // 604 - Actual Tramline Condensed Work State (33-48)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_49_64 	605	 // 605 - Actual Tramline Condensed Work State (49-64)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_65_80 	606	 // 606 - Actual Tramline Condensed Work State (65-80)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_81_96 	607	 // 607 - Actual Tramline Condensed Work State (81-96)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_97_112 	608	 // 608 - Actual Tramline Condensed Work State (97-112)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_113_128 	609	 // 609 - Actual Tramline Condensed Work State (113-128)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_129_144 	610	 // 610 - Actual Tramline Condensed Work State (129-144)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_145_160 	611	 // 611 - Actual Tramline Condensed Work State (145-160)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_161_176 	612	 // 612 - Actual Tramline Condensed Work State (161-176)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_177_192 	613	 // 613 - Actual Tramline Condensed Work State (177-192)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_193_208 	614	 // 614 - Actual Tramline Condensed Work State (193-208)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_209_224 	615	 // 615 - Actual Tramline Condensed Work State (209-224)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_225_240 	616	 // 616 - Actual Tramline Condensed Work State (225-240)
#define DDI_ACTUAL_TRAMLINE_CONDENSED_WORK_STATE_241_256 	617	 // 617 - Actual Tramline Condensed Work State (241-256)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_17_32 	618	 // 618 - Setpoint Tramline Condensed Work State (17-32)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_33_48 	619	 // 619 - Setpoint Tramline Condensed Work State (33-48)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_49_64 	620	 // 620 - Setpoint Tramline Condensed Work State (49-64)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_65_80 	621	 // 621 - Setpoint Tramline Condensed Work State (65-80)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_81_96 	622	 // 622 - Setpoint Tramline Condensed Work State (81-96)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_97_112 	623	 // 623 - Setpoint Tramline Condensed Work State (97-112)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_113_128 	624	 // 624 - Setpoint Tramline Condensed Work State (113-128)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_129_144 	625	 // 625 - Setpoint Tramline Condensed Work State (129-144)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_145_160 	626	 // 626 - Setpoint Tramline Condensed Work State (145-160)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_161_176 	627	 // 627 - Setpoint Tramline Condensed Work State (161-176)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_177_192 	628	 // 628 - Setpoint Tramline Condensed Work State (177-192)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_193_208 	629	 // 629 - Setpoint Tramline Condensed Work State (193-208)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_209_224 	630	 // 630 - Setpoint Tramline Condensed Work State (209-224)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_225_240 	631	 // 631 - Setpoint Tramline Condensed Work State (225-240)
#define DDI_SETPOINT_TRAMLINE_CONDENSED_WORK_STATE_241_256 	632	 // 632 - Setpoint Tramline Condensed Work State (241-256)
#define DDI_PGN_BASED_DATA	57342	 // 57342 - PGN Based Data
#define DDI_REQUEST_DEFAULT_PROCESS_DATA	57343	 // 57343 - Request Default Process Data
#define DDI_65534_PROPRIETARY_DDI_RANGE	57344	 // 57344 - 65534 Proprietary DDI Range
#define DDI_RESERVED	65535	 // 65535 - Reserved



#endif /* DDI_H */
