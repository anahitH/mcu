/*

 Copyright (c) 2015 Douglas J. Bakkum

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
 OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.

*/



#ifndef _COMMANDER_H_
#define _COMMANDER_H_


#include <stdint.h>
#include "memory.h"
#include "jsmn.h"
#ifndef TESTING
#include "conf_usb.h"

#define COMMANDER_REPORT_SIZE   UDI_HID_REPORT_OUT_SIZE
#else
#define COMMANDER_REPORT_SIZE   2048
#endif

#define DIGITAL_BITBOX_VERSION  "1.0"

#define COMMANDER_MAX_ATTEMPTS	5// max attempts before device reset

#define VERIFYPASS_FILENAME     "verification.txt"

#define GENERATE_STRING(STRING) #STRING,
#define GENERATE_ENUM_ATTR(ENUM) ATTR_ ## ENUM ## _,
#define GENERATE_ENUM_CMD(ENUM) CMD_ ## ENUM ## _,

#define FOREACH_CMD(CMD)        \
  /*    parent commands     */  \
  /*    requiring touch     */  \
        CMD(sign)               \
        CMD(seed)               \
        CMD(password)           \
        CMD(touchbutton)        \
  /* placeholder don't move */  \
        CMD(require_touch)      \
  /*    parent commands     */  \
  /*    not requiring touch */  \
        CMD(led)                \
        CMD(xpub)               \
        CMD(name)               \
        CMD(echo)               \
        CMD(reset)              \
        CMD(random)             \
        CMD(backup)             \
        CMD(device)             \
        CMD(verifypass)         \
        CMD(ciphertext)         \
  /*    child commands      */  \
        CMD(timeout)            \
        CMD(holdtime)           \
        CMD(threshold)          \
        CMD(generate)           \
        CMD(source)             \
        CMD(id)                 \
        CMD(type)               \
        CMD(data)               \
        CMD(keypath)            \
        CMD(change_keypath)     \
        CMD(strength)           \
        CMD(salt)               \
        CMD(filename)           \
        CMD(decrypt)            \
        CMD(encrypt)            \
  /* placeholder don't move */  \
        CMD(none)                /* keep last */

#define FOREACH_ATTR(ATTR)      \
  /*    command attributes  */  \
        ATTR(transaction)       \
        ATTR(hash)              \
        ATTR(true)              \
        ATTR(list)              \
        ATTR(erase)              \
        ATTR(toggle)            \
        ATTR(pseudo)            \
        ATTR(create)            \
        ATTR(export)            \
        ATTR(serial)            \
        ATTR(version)           \
        ATTR(__ERASE__)         \
        ATTR(__FORCE__)         \
        ATTR(none)               /* keep last */

enum CMD_ENUM { FOREACH_CMD(GENERATE_ENUM_CMD) };
enum ATTR_ENUM { FOREACH_ATTR(GENERATE_ENUM_ATTR) };

#define CMD_NUM      CMD_none_
#define ATTR_NUM     ATTR_none_

enum REPORT_FLAGS { 
    SUCCESS, ERROR, 
    ECHO,
    SAME, DIFFERENT,
    TOUCHED, NOT_TOUCHED,
    RESET
};


void commander_force_reset(void);
void commander_fill_report(const char *attr, const char *val, int err);
void commander_fill_report_len(const char *attr, const char *val, int err, int vallen);
void commander_fill_report_signature(const uint8_t *sig, const uint8_t *pubkey, const char *id, size_t id_len);
void commander_create_verifypass(void);
char *commander(const char *instruction_encrypted);

char *aes_cbc_b64_encrypt(const unsigned char *in, int inlen, int *out_b64len, PASSWORD_ID id);
char *aes_cbc_b64_decrypt(const unsigned char *in, int inlen, int *decrypt_len, PASSWORD_ID id);

#endif
