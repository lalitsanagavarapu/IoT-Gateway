/*==========================LICENSE NOTICE==========================*/
/*
Copyright (c) 2009-2017 Vidcentum R&D Pvt Ltd. All Rights Reserved.
Author: Vidcentum R&D (research@vidcentum.com)
*/

/*
The software and services are confidential and proprietary of Vidcentum R&D Pvt Ltd. 
You shall not disclose such Confidential Information and shall use it only in 
accordance with the terms of the license agreement you entered with Vidcentum R&D.
Vidcentum R&D acknowledges and honours the opensource software modules and
respective licenses. 

The software is distributed with source to its users / customers / stakeholders. 

Please see the TERMS OF USE OF THE SOFTWARE below before using this software.

Type of Software: Application
External Libraries: This software uses external libraries with licenses MIT, GPL, Apache etc.
The software is distributed with source to its users / customers as part of its
service contract. It will comply with all or most of licenses of external libraries.
*/

/* 
TERMS OF USE OF THE SOFTWARE by Vidcentum R&D Pvt Ltd
======================================================
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

Ref: https://www.gnu.org/copyleft/gpl.html Sections 15, 16 and 17.

A Disclaimer of Warranty.
=========================
THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. 
EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER 
PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED 
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE 
OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST 
OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

B Limitation of Liability.
==========================
IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY 
COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS 
PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, 
INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE 
THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED 
INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM 
TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

C Interpretation of Sections A and B.
=====================================
If the disclaimer of warranty and limitation of liability provided above cannot be 
given local legal effect according to their terms, reviewing courts shall apply local 
law that most closely approximates an absolute waiver of all civil liability in connection 
with the Program, unless a warranty or assumption of liability accompanies a copy of 
the Program in return for a fee.
*/
/*==========================END LICENSE NOTICE==========================*/   

#ifndef _VC_SF_IDK_OPC_PACKML_TYPES_H_
#define _VC_SF_IDK_OPC_PACKML_TYPES_H_

#include <string>
#include <vector>
/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Clause 7.4 of ANSI/ISA-TR88.00.02-2015
 * Data types
 *
 */

/*
 * Unsigned octet integer
 * Symbol: PACKML_UInt8
 * Size: 1 octet
 * IDL: typedef octet PACKML_UInt8;
 * This data type represents positive integers from 0 to 255.
 */
typedef unsigned char PACKML_UInt8;
typedef PACKML_UInt8 PACKML_octet;
typedef PACKML_UInt8 PACKML_Octet;

/*
 * SByte
 * An integer value between -128 and 127.
 */
typedef int8_t PACKML_SByte;
#define PACKML_SBYTE_MAX 127
#define PACKML_SBYTE_MIN (-128)

/*
 * Byte
 * An integer value between 0 and 256.
 */
typedef uint8_t PACKML_Byte;
#define PACKML_BYTE_MAX 256
#define PACKML_BYTE_MIN 0

/*
 * Unsigned 16 bit integer
 * Symbol: PACKML_UInt16
 * Size: 2 octets
 * IDL: typedef unsigned short PACKML_UInt16;
 * A PACKML_UInt16 may take any value between 0 and 65 535.
 *
 */
typedef unsigned short int PACKML_UInt16;

/*
 * Signed 32 bit integer
 * Symbol: PACKML_Int32
 * Size: 4 octets
 * IDL: typedef long PACKML_Int32;
 * This data type is used to represent a signed integer from
 * –2 147 483 648 to 2 147 483 647.
 *
 */
typedef long PACKML_Int32;

/*
 * Unsigned 32 bit integer
 * Symbol: PACKML_UInt32
 * Size: 4 octets
 * IDL: typedef unsigned long PACKML_UInt32;
 * This data type is used to represent positive integers from 0 to 4 294 967 295.
 *
 */
typedef unsigned long PACKML_UInt32;

/*
 * Single-precision real
 * Symbol: PACKML_Float32
 * Size: 4 octets
 * IDL: typedef float PACKML_Float32;
 * A single-precision real number is a 32 bit binary sequence that encodes real
 * numbers as specified in IEEE Std 754-1985.
 *
 */
typedef float PACKML_Float32;

/*
 * Floating-point NaN in TEDS According to IEEE Std 754-1985, a single precision
 * number with an exponent of 255 and a fractional portion (mantissa) that is nonzero
 * is NaN regardless of the sign bit. The recommended value for use in a TEDS field for
 * NaN is 0x7FFFFFFF (hex).
 * Note: Take care of this in implenentation. Use standard library wherever applicable.
 *
 */
#define PACKML_NaN 0x7FFFFFFF

/*
 * Double-precision real
 * Symbol: PACKML_Float64
 * Size: 8 octets
 * IDL: typedef double PACKML_Float64;
 * A double-precision real number is a 64 bit binary sequence that encodes real numbers
 * as specified in IEEE Std 754-1985.
 *
 */
typedef double PACKML_Float64;

/*
 * String
 * Symbol: PACKML_String
 * Size: variable (Upto 80)
 * IDL: typedef string PACKML_String;
 *
 */
typedef std::string PACKML_String;

/*
 * Boolean
 * Symbol: PACKML_Boolean
 * Size: 1 octet
 * IDL: typedef boolean PACKML_Boolean;
 * The type Boolean is a basic type that is defined in the OMG standards for IDL.
 * For the purposes of this standard, a bit or octet with a nonzero value is considered True.
 * A zero value represents the False state of the variable.
 *
 */
typedef bool PACKML_Boolean;

/*
 * Date and Time
 * Symbol: PACKML_DateTime
 * Size: Array of 7 PACKML_Int32
 * IDL: typedef boolean PACKML_DateTime;
 *
 */
typedef struct PACKML_DateTime
{
    PACKML_Int32 packmlDT[7];

} PACKML_DateTime;

/*
 * Data types for associated applications
 */

/*
 * Eight bit signed integer
 * Symbol: PACKML_Int8
 * Size: 1 octet
 * IDL: typedef char PACKML_Int8;
 * This datatype represents integers from –128 to 127.
 */
typedef char PACKML_Int8;

/*
 * Sixteen bit signed integer
 * Symbol: PACKML_Int16
 * Size: 2 octets
 * IDL: typedef short PACKML_Int16;
 * This data type represents integers from –32 768 to 32 767.
 */
typedef short PACKML_Int16;
typedef short PACKML_Short;

/*
 * Arbitrary octet array
 * Symbol: PACKML_OctetArray
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate
 * entity that may or may not be interpreted as a number. An OctetArray can be a structure
 * comrpising one or more primitive data types, arrays of primitive data types, or
 * smaller OctetArrays.
 */
typedef PACKML_Octet PACKML_OctetArrays;

/*
 * String array
 * Symbol: PACKML_StringArray
 * Size: varies
 * This data type comprises an arbitrary number of string data types, treated
 * as an aggregate entity.
 */
typedef PACKML_String PACKML_StringArray;

/*
 * Boolean array
 * Symbol: PACKML_BooleanArray
 * Size: varies
 * This data type comprises an arbitrary number of _boolean data types,
 * treated as an aggregate entity.
 */
typedef PACKML_Boolean PACKML_BooleanArray;

/*
 * Array of 8 bit signed integers
 * Symbol: PACKML_Int8Array;
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate
 * entity made up of 8 bit signed integers (Int8).
 */
typedef std::vector<PACKML_Int8> PACKML_Int8Array;

/*
 * Array of 16 bit signed integers
 * Symbol: PACKML_Int16Array;
 * Size: varies
 * This data type comprises an arbitrary number of 16 bit signed integers (PACKML_Int16),
 * treated as an aggregate entity.
 */
typedef std::vector<PACKML_Int16> PACKML_Int16Array;

/*
 * Array of 32 bit signed integers
 * Symbol: PACKML_Int32Array;
 * Size: varies
 * This data type comprises an arbitrary number of 32 bit signed integers (PACKML_Int32),
 * treated as an aggregate entity.
 */
typedef std::vector<PACKML_Int32> PACKML_Int32Array;

/*
 * Symbol: PACKML_UInt8Array;
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate entity
 * made up of 8 bit unsigned integers (PACKML_UInt8).
 */
typedef std::vector<PACKML_UInt8> PACKML_UInt8Array;

/*
 * Array of 16 bit unsigned integers
 * Symbol: PACKML_UInt16Array;
 * Size: varies
 * This data type comprises an arbitrary number of 16 bit unsigned integers (PACKML_UInt16),
 * treated as an aggregate entity.
 */
typedef std::vector<PACKML_UInt16> PACKML_UInt16Array;

/*
 * Array of 32 bit unsigned integers
 * Symbol: PACKML_UInt32Array;
 * Size: varies
 * This data type comprises an arbitrary number of 32 bit signed integers (PACKML_UInt32),
 * treated as an aggregate entity.
 */
typedef std::vector<PACKML_UInt32> PACKML_UInt32Array;

/*
 * Array of single-precision real numbers
 * Symbol: PACKML_Float32Array;
 * Size: varies
 * This data type comprises an arbitrary number of single-precision real numbers as
 * specified in IEEE Std 754-1985, treated as an aggregate entity.
 */
typedef std::vector<PACKML_Float32> PACKML_Float32Array;

/*
 * Array of double-precision real numbers
 * Symbol: PACKML_Float64Array;
 * Size: varies
 * This data type comprises an arbitrary number of double-precision real numbers as
 * specified in IEEE Std 754-1985, treated as an aggregate entity.
 */
typedef std::vector<PACKML_Float64> PACKML_Float64Array;

/////////// PROTCOL TYPES /////////////

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_OPC_PACKML_TYPES_H_ */
