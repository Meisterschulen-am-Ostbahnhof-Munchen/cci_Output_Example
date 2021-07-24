/*
 * CanDriverEsp32.h
 *
 *  Created on: 16.06.2021
 *      Author: FranzHoepfinger
 */

#ifndef COMPONENTS_APPCANDRIVERESP32_CANDRIVERESP32_H_
#define COMPONENTS_APPCANDRIVERESP32_CANDRIVERESP32_H_


void     hw_CanInit(uint8_t maxCanNodes_u8);
void     hw_CanClose(void);
int16_t  hw_CanSendMsg(uint8_t canNode_u8, uint32_t canId_u32, const uint8_t canData_au8[], uint8_t canDataLength_u8);
int16_t  hw_CanReadMsg(uint8_t canNode_u8, uint32_t *canId_pu32, uint8_t canData_pau8[], uint8_t *canDataLength_pu8);
int16_t  hw_CanGetFreeSendMsgBufferSize(uint8_t canNode_u8);



#endif /* COMPONENTS_APPCANDRIVERESP32_CANDRIVERESP32_H_ */
