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

#ifndef _VC_SF_IDK_21450_2010_TYPES_H_
#define _VC_SF_IDK_21450_2010_TYPES_H_

#include <string>
#include <vector>
/* Begin of the 'extern "C"' block */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef VC_SF_IDK_EXTERN
#define VC_SF_IDK_EXTERN extern
#endif
#ifndef VC_SF_IDK_API
#define VC_SF_IDK_API
#endif
#ifndef VC_SF_IDK_CDECL
#define VC_SF_IDK_CDECL
#endif
#ifndef VC_SF_IDK_STDCALL
#define VC_SF_IDK_STDCALL
#endif

#define VC_SF_IDK_DEPRECATED
#define VC_SF_IDK_EXPERIMENTAL

/*
 * Let's have versioning of Smart Factory IDK
 */
#define VC_SF_IDK_VERSION "0x0A"
#define VC_SF_IDK_NUMBER 10

// The following HTTP constants are used by NCAP Controller
// and Embedded HTTP Servers.
#define VC_SF_HTTP_POST_BUFFER_SIZE 512
#define VC_SF_HTTP_MAX_NAME_SIZE 20
#define VC_SF_HTTP_MAX_ANSWER_SIZE 512
#define VC_SF_HTTP_GET 0
#define VC_SF_HTTP_POST 1

/*
 * Zeros and Ones...
 */
#ifndef VC_SF_IDK_ZERO
#ifdef VC_SF_IDK_XDOUBLE
#define VC_SF_IDK_ZERO 0.e0L
#define ZERO 0.e0L
#elif defined VC_SF_IDK_DOUBLE
#define VC_SF_IDK_ZERO 0.e0
#define ZERO 0.e0
#else
#define VC_SF_IDK_ZERO 0.e0f
#define ZERO 0.e0f
#endif
#endif

#ifndef VC_SF_IDK_ONE
#ifdef VC_SF_IDK_XDOUBLE
#define VC_SF_IDK_ONE 1.e0L
#define ONE 1.e0L
#elif defined VC_SF_IDK_DOUBLE
#define VC_SF_IDK_ONE 1.e0
#define ONE 1.e0
#else
#define VC_SF_IDK_ONE 1.e0f
#define ONE 1.e0f
#endif
#endif

// STATISTICAL CONSTANTS
#define VC_SF_MAX_DATASET_SIZE_FOR_RSTATS 1000
#define VC_SF_MAX_DATASET_SIZE_FOR_RECORDER 1000100

/*
 * Clause 4 of ISO/IEC/IEEE 21450:2010
 * Data types
 *
 */

/*
 * 4.1 Unsigned octet integer
 * Symbol: UInt8
 * Size: 1 octet
 * IDL: typedef octet UInt8;
 * This data type represents positive integers from 0 to 255.
 */
typedef unsigned char UInt8;
typedef UInt8 octet;
typedef UInt8 Octet;

/*
 * 4.2 Unsigned 16 bit integer
 * Symbol: UInt16
 * Size: 2 octets
 * IDL: typedef unsigned short UInt16;
 * A UInt16 may take any value between 0 and 65 535.
 *
 */
typedef unsigned short int UInt16;

/*
 * 4.3 Signed 32 bit integer
 * Symbol: Int32
 * Size: 4 octets
 * IDL: typedef long Int32;
 * This data type is used to represent a signed integer from
 * –2 147 483 648 to 2 147 483 647.
 *
 */
typedef long Int32;

/*
 * 4.4 Unsigned 32 bit integer
 * Symbol: UInt32
 * Size: 4 octets
 * IDL: typedef unsigned long UInt32;
 * This data type is used to represent positive integers from 0 to 4 294 967 295.
 *
 */
typedef unsigned long UInt32;

/*
 * 4.5 Single-precision real
 * Symbol: Float32
 * Size: 4 octets
 * IDL: typedef float Float32;
 * A single-precision real number is a 32 bit binary sequence that encodes real
 * numbers as specified in IEEE Std 754-1985.
 *
 */
typedef float Float32;

/*
 * 4.5.1 Floating-point NaN in TEDS According to IEEE Std 754-1985, a single precision
 * number with an exponent of 255 and a fractional portion (mantissa) that is nonzero
 * is NaN regardless of the sign bit. The recommended value for use in a TEDS field for
 * NaN is 0x7FFFFFFF (hex).
 * Note: Take care of this in implenentation. Use standard library wherever applicable.
 *
 */
#define VC_SF_IDK_NaN 0x7FFFFFFF

/*
 * 4.6 Double-precision real
 * Symbol: Float64
 * Size: 8 octets
 * IDL: typedef double Float64;
 * A double-precision real number is a 64 bit binary sequence that encodes real numbers
 * as specified in IEEE Std 754-1985.
 *
 */
typedef double Float64;

/*
 * 4.7 String
 * Symbol: _String
 * Size: variable
 * IDL: typedef string _String; // Leading '_' to escape reserved IDL keyword
 * The use of text strings, as type string as a basic type that is defined in IEEE Std
 * 1451.2-1997, has been replaced with the use of OMG standards for IDL.
 * The XML used in 8.9 is the text-based TEDS. The controlling document for XML is the W3C
 * Recommendation Extensible Markup Language (XML) 1.0 (Second Edition). All text strings
 * in the TEDS shall conform to this recommendation or to a future update to it.
 *
 */
typedef std::string _String;

/*
 * 4.8 Boolean
 * Symbol: _Boolean
 * Size: 1 octet
 * IDL: typedef boolean _Boolean; // Leading '_' to escape reserved IDL keyword
 * The type Boolean is a basic type that is defined in the OMG standards for IDL.
 * For the purposes of this standard, a bit or octet with a nonzero value is considered True.
 * A zero value represents the False state of the variable.
 *
 */
typedef bool _Boolean;

/*
 * 4.9 IEEE1451Dot0::Args::TimeRepresentation
 * This abstract class defines the time representation. It is subclassed into TimeInstance
 * and TimeDuration. The definition of the two arguments is given in Table 1.
 * IDL: struct TimeRepresentation
 *      {
 *          UInt32 secs;
 *          UInt32 nsecs;
 *      };
 * Seconds—This unsigned 32 bit number represents the number of seconds from the
 * beginning of the epoch (normally 0 hours on 1 January 1970).
 * Sign, Nanoseconds—This unsigned 32 bit integer comprises two smaller fields. The most
 * significant bit will be interpreted as the sign bit of the entire time value. The least
 * significant 31 bits represent the number of nanoseconds to be added to the value
 * identified by the Seconds field before the sign is applied. The value specified in the
 * Nanoseconds field is constrained to the domain 0 to 999 999 999, inclusive.
 *
 * NOTE—This format is corrected for the flaw in negative time representation discovered
 * in IEEE Std 1588-2002.
 *
 */
typedef struct TimeRepresentation TimeRepresentation;
struct TimeRepresentation
{
    UInt32 secs;
    UInt32 nsecs;
};

/*
 * This subclass of time representation is used to specify a time interval rather than
 * a time value. The definition of the two arguments is the same as shown in 4.9.
 * IDL: struct TimeDuration
 *      {
 *          UInt32 secs;
 *          UInt32 nsecs;
 *      };
 *
 */
typedef struct TimeDuration TimeDuration;
struct TimeDuration
{
    UInt32 secs;
    UInt32 nsecs;
};

/*
 * 4.9.2 IEEE1451Dot0::Args::TimeInstance
 * Time values are represented by this struct in the IEEE 1451.0 layer. This struct is
 * appropriate when trying to represent a time value and not time duration. A time value
 * that occurs before the epoch is specified by a negative “nsecs” field.
 * IDL: struct TimeInstance
 *      {
 *         UInt32 secs;
 *         UInt32 nsecs;
 *      };
 * The TimeInstance is based on an epoch that is defined as starting at midnight 1 January
 * 1970. The definition of the two arguments is the same as shown in 4.9.
 *
 */
typedef struct TimeInstance TimeInstance;
struct TimeInstance
{
    UInt32 secs;
    UInt32 nsecs;
};

/*
 * 4.10 Data types for associated applications
 */

/*
 * 4.10.1 Eight bit signed integer
 * Symbol: Int8
 * Size: 1 octet
 * IDL: typedef char Int8;
 * This datatype represents integers from –128 to 127.
 */
typedef char Int8;

/*
 * 4.10.2 Sixteen bit signed integer
 * Symbol: Int16
 * Size: 2 octets
 * IDL: typedef short Int16;
 * This data type represents integers from –32 768 to 32 767.
 */
typedef short Int16;
typedef short Short;

/*
 * 4.11 Physical Units
 * Symbol: UNITS Size: 11 octets
 * IDL: struct Units
 *      {
 *          UInt8   interpretation;
 *          UInt8   radians;
 *          UInt8   steradians;
 *          UInt8   meters;
 *          UInt8   kilograms;
 *          UInt8   seconds;
 *          UInt8   amperes;
 *          UInt8   kelvins;
 *          UInt8   moles;
 *          UInt8   candelas
 *          UInt8   UnitsExtensionTEDSAccessCode;
 *       };
 * Physical Units are a binary sequence of 10 octets that encode Physical Units as described
 * in Table 2 and Table 3. Each field shall be interpreted as an unsigned integer. A unit
 * shall be represented as a product of the SI base units, plus radians and steradians, each
 * raised to a rational power. This structure encodes only the exponents; the product is
 * implicit.
 *
 */
typedef struct Units Units;
struct Units
{
    UInt8 interpretation;
    UInt8 radians;
    UInt8 steradians;
    UInt8 meters;
    UInt8 kilograms;
    UInt8 seconds;
    UInt8 amperes;
    UInt8 kelvins;
    UInt8 moles;
    UInt8 candelas;
    UInt8 UnitsExtensionTEDSAccessCode;
};

/*
 * Manifest constants
 */
typedef enum {
    PUI_SI_UNITS = 0,
    PUI_RATIO_SI_UNITS = 1,
    PUI_LOG10_SI_UNITS = 2,
    PUI_LOG10_RATIO_SI_UNITS = 3,
    PUI_DIGITAL_DATA = 4,
    PUI_ARBITRARY = 5
} PhysicalUnitsInterpretation;

/*
 * 4.12 Universal unique identification
 * Symbol: UUID
 * Size: 10 octets
 * IDL: typedef UUID Short [5];
 * Location field:          42 bits
 * Manufacturer’s field:     4 bits
 * Year field:              12 bits
 * Time field:              22 bits
 *
 */
typedef struct UUID UUID;
struct UUID
{
    Short uuid[5];
};

/*
 * 4.13 Arbitrary octet array
 * Symbol: OctetArray
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate
 * entity that may or may not be interpreted as a number. An OctetArray can be a structure
 * comrpising one or more primitive data types, arrays of primitive data types, or
 * smaller OctetArrays.
 */
typedef Octet OctetArrays;

/*
 * 4.14 String array
 * Symbol: StringArray
 * Size: varies
 * This data type comprises an arbitrary number of string data types (see 4.7), treated
 * as an aggregate entity.
 */
typedef _String StringArray;

/*
 * 4.15 Boolean array
 * Symbol: BooleanArray
 * Size: varies
 * This data type comprises an arbitrary number of _boolean data types (see 4.7),
 * treated as an aggregate entity.
 */
typedef _Boolean BooleanArray;

/*
 * 4.16 Array of 8 bit signed integers
 * Symbol: Int8Array;
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate
 * entity made up of 8 bit signed integers (Int8).
 */
typedef std::vector<Int8> Int8Array;

/*
 * 4.17 Array of 16 bit signed integers
 * Symbol: Int16Array;
 * Size: varies
 * This data type comprises an arbitrary number of 16 bit signed integers (Int16),
 * treated as an aggregate entity.
 */
typedef std::vector<Int16> Int16Array;

/*
 * 4.18 Array of 32 bit signed integers
 * Symbol: Int32Array;
 * Size: varies
 * This data type comprises an arbitrary number of 32 bit signed integers (Int32),
 * treated as an aggregate entity.
 */
typedef std::vector<Int32> Int32Array;

/*
 * Symbol: UInt8Array;
 * Size: varies
 * This data type comprises an arbitrary number of octets, treated as an aggregate entity
 * made up of 8 bit unsigned integers (UInt8).
 */
typedef std::vector<UInt8> UInt8Array;

/*
 * 4.20 Array of 16 bit unsigned integers
 * Symbol: UInt16Array;
 * Size: varies
 * This data type comprises an arbitrary number of 16 bit unsigned integers (UInt16),
 * treated as an aggregate entity.
 */
typedef std::vector<UInt16> UInt16Array;

/*
 * 4.21 Array of 32 bit unsigned integers
 * Symbol: UInt32Array;
 * Size: varies
 * This data type comprises an arbitrary number of 32 bit signed integers (UInt32),
 * treated as an aggregate entity.
 */
typedef std::vector<UInt32> UInt32Array;

/*
 * 4.22 Array of single-precision real numbers
 * Symbol: Float32Array;
 * Size: varies
 * This data type comprises an arbitrary number of single-precision real numbers as
 * specified in IEEE Std 754-1985, treated as an aggregate entity.
 */
typedef std::vector<Float32> Float32Array;

/*
 * 4.23 Array of double-precision real numbers
 * Symbol: Float64Array;
 * Size: varies
 * This data type comprises an arbitrary number of double-precision real numbers as
 * specified in IEEE Std 754-1985, treated as an aggregate entity.
 */
typedef std::vector<Float64> Float64Array;

/*
 * 4.24 Array of TimeDuration data types
 * Symbol: TimeDurationArray;
 * Size: varies
 * This data type comprises an arbitrary number of TimeDuration data types as specified
 * in 4.9.1, treated as an aggregate entity.
 */
typedef std::vector<TimeDuration> TimeDurationArray;

/*
 * 4.25 Array of TimeInstance data types
 * Symbol: TimeInstanceArray;
 * Size: varies
 * This data type comprises an arbitrary number of TimeInstance data types as specified
 * in 4.9.2, treated as an aggregate entity.
 */
typedef std::vector<TimeInstance> TimeInstanceArray;

/////////// PROTCOL TYPES /////////////

// NCAP CONTROLLER API. Refer: SFMain, for example, CSFThings2Pack::sfMain()
// get_cyber_physical_config_api, m_post_cyber_physical_config_api
// POST Key: post_new_cyber_physical_config_key
// json11::Json jcp =
// json11::Json jCyberPhysicalConfig = json11::Json::object
//                                     {
//                                          {"transducer_definitions",  "transducer definitions"},
//                                          {"product_rules",  "product rules"},
//                                          {"assets",  "assets"},
//                                          { "erp_node", "erp_node" },
//                                          { "opc_node", "opc_node" }
//                                     };

// TRANSDUCER CHANNEL ENVELOPE TYPE ENUMERATIONS
// IDENTIFIERS / KEYS / NAMES in a JSON
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_META_IDENTIFIER ("Meta-Transducer-Channel-Envelope")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_IDENTIFIER ("Transducer-Channel-Envelope")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_IDENTIFIER_NAME ("name")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_TYPE ("type")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_LENGTH ("length")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_response ("response")

/*
 *  Example:
 *  {"Meta-Transducer-Channel-Envelope", json11::Json::object
 *      {"name", "Transducer-Channel-Envelope"},
 *      {"type", "s_int"}               // Envelope Type
 *      {"length", 0},                  // The Transducer Modules fill the data read.
 *      {"response", "response_json"},  // The Transducer Modules build response packet.
 *  }
 *
 */

#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BIT ("s_bit")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BOOLEAN ("s_bool")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_INT ("s_int")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE ("s_double")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_FLOAT ("s_float")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE_FLOAT ("s_double_float")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_OCTET ("s_octet")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_GPS ("s_gps")

#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BIT_ARRAY ("s_bit_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BOOLEAN_ARRAY ("s_bool_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_INT_ARRAY ("s_int_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE_ARRAY ("s_double_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_FLOAT_ARRAY ("s_float_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE_FLOAT_ARRAY ("s_double_float_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_OCTET_ARRAY ("s_octet_array")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_GPS_ARRAY ("s_gps_array")

#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BIT_VECTOR ("s_bit_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_BOOLEAN_VECTOR ("s_bool_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_INT_VECTOR ("s_int_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE_VECTOR ("s_double_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_FLOAT_VECTOR ("s_float_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_DOUBLE_FLOAT_VECTOR ("s_double_float_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_OCTET_VECTOR ("s_octet_vector")
#define VC_SF_TRANSDUCER_CHANNEL_ENVELOPE_SCALAR_GPS_VECTOR ("s_gps_vector")

// DO NOT CHNAGE THE ORDER OF THE ELEMENTS.
/* Transducer Response Dataset*/
typedef struct TransducerResponseDataSet
{
    double timestamp; // Timestamp
    int response;     // Response
    int capabilities; // Capabilities
    int status;       // Status
    int alarms;       // Alarms

} TransducerResponseDataSet;

// TBD of Array Sizes.
/* Smart Factory Library Dataset*/
typedef struct SFLibraryDataSet
{
    char assets[10 * 1024];
    char products[10 * 1024];
    char transducers[10 * 1024];
    char preset[30 * 1024];
} SFLibraryDataSet;

#ifdef __cplusplus
} /* end of the 'extern "C"' block */
#endif

#endif /* _VC_SF_IDK_21450_2010_TYPES_H_ */
