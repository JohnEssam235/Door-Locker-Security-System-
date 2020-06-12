 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "i2c.h"  // 3mlt include ll i2c 34an ast3ml el functions bta3to ..............

// hena ana 3mlt include l driver el i2c gowa driver el EEPROM ..... tab leh m3mlt4 include ll i2c.h gowa el header bta3 el eeprom m4 el .c file bta3o ????  la2n ana lw kont 3mltlo include gowa el header bta3o w b3dha 3mlt ll(eeprom.h) include gowa el main fa kda el main feha el driver bta3 el eeprom el gowah aslun driver el i2c w dy 7aga m4 7lwa mmkn tedorny ........fa 34an kda 3mlto include gowa el .c m4 el .h bta3 el eeprom.......asma3 el record......

#include "external_eeprom.h"

void EEPROM_init(void)  // lama a43'l el EEPROM kda ana sha3'alt el I2C ............mmkn ageb EEPROM t4t3'l m3 SPI msln fa hya hya lama a43'l el EEPROM h43'l el I2C ....la2n el I2C howa el by43'l el memory dy............
{
	/* just initialize the I2C(TWI) module inside the MC */
	TWI_init();
}

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)  // h3ml write(y3ny hkteb f el EEPROM). ...fa hya bta5od awl 7aga address el memory loc. el hykteb feh 34an kda 3mlto uint16 la2no 11 bits ......w hta5od el data el htktbha (el eeprom ht5zn el data dy f el address da el enta ba3ethom) ... fa dlw2ty ana 3ayz a3ml write ...yb2a lazm a3ml el frame b2a..............yb2a el func dy bta5od el address el gowa el eeprom el ht5zn feh el data bta3tak w hta5od el data el ht5znha ..........................
{
	/* Send the Start Bit */
    TWI_start(); // awl 7aga hb3at el start bit bl I2C ........
    if (TWI_getStatus() != TW_START)   // lw el status m4 b TW_START m3na kda en fe mo4kla 7slt w eno m3ml4 start bit ..... fa hb3at error(raga3ly error y3ny)..............
        return ERROR;


		// b3d kda el mafrod hb3at el slave address ..............

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)  // hyrod 3lya b ack............
        return ERROR; 
		 
    /* Send the required memory location address */
    TWI_write((uint8)(u16addr));    // h3mel casting b uint8 la2ny hb3at awl 8 bs la2n el 3 MSB atb3to 5las m3 el slave address....
    if (TWI_getStatus() != TW_MT_DATA_ACK) // rod 3lya b ack................
        return ERROR;
		
    /* write byte to eeprom */
    TWI_write(u8data);    // hb3at el data ll EEPROM ...el data dy el hya gaya ll function el hya uint8 u8data dy.................
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;


    /* Send the Stop Bit */
    TWI_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)  // hena lw 3ayz a2ra mn el EEPROM .........hb3tlo el mem. loc el h2ra meno w hb3tlo el variable el ha5od feh el data dy ....w lazm ab3at el variable da by address 34an mytms74 tab3an......
{
	/* Send the Start Bit */
    TWI_start();  // awl 7aga ab3at el start bit
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));  // hb3at el slave address ...fa el awl h3mel write .......w adeha el slave address bl equation bta3ty ......
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)  // hst2bl ack
        return ERROR;
		
    /* Send the required memory location address */
    TWI_write((uint8)(u16addr));   // hb3t el mem loc.
    if (TWI_getStatus() != TW_MT_DATA_ACK)  // ast2bl ack....
        return ERROR;
		
    // dlw2ty ana 3ayz a-read mn el eeprom fa dy kda combined message ....fa lazm ab3at el frame tany ..................

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_REP_START)  // hb3at repeated start ...........
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));      // hb3at el slave address bs el mara dy 3ayz a3ml read fa h3mel OR m3 1 fe el equation.................
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNACK();  // h7ot el data el gaya mn el read(el data el h2raha mn el eeprom y3ny) fe el variable el ana ba3to by ref. da.............
    if (TWI_getStatus() != TW_MR_DATA_NACK)   // yerod b nack ......
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
    return SUCCESS;
}
