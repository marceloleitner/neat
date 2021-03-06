#ifndef NEAT_QOS_H
#define NEAT_QOS_H

#include "neat.h"
#include "neat_internal.h"

#define NEAT_QOS_DEFAULT 0x00

#define NEAT_DSCP_BE    0x00
#define NEAT_DSCP_DF    0x00
#define NEAT_DSCP_EF    0x2E
#define NEAT_DSCP_AF11  0x0A
#define NEAT_DSCP_AF12  0x0C
#define NEAT_DSCP_AF13  0x0E
#define NEAT_DSCP_AF21  0x12
#define NEAT_DSCP_AF22  0x14
#define NEAT_DSCP_AF23  0x16
#define NEAT_DSCP_AF31  0x1A
#define NEAT_DSCP_AF32  0x1C
#define NEAT_DSCP_AF33  0x1E
#define NEAT_DSCP_AF41  0x22
#define NEAT_DSCP_AF42  0x24
#define NEAT_DSCP_AF43  0x26
#define NEAT_DSCP_CS0   0x00
#define NEAT_DSCP_CS1   0x08
#define NEAT_DSCP_CS2   0x10
#define NEAT_DSCP_CS3   0x18
#define NEAT_DSCP_CS4   0x20
#define NEAT_DSCP_CS5   0x28
#define NEAT_DSCP_CS6   0x30
#define NEAT_DSCP_CS7   0x38

//Suffix Priority (Very_Low, Low, Medium, High)
//Prefix (Interactive,Non_Interactive,Immersive,Admitted)
#define NEAT_QOS_AUDIO_VL                  NEAT_DSCP_CS1
#define NEAT_QOS_AUDIO_L                   NEAT_DSCP_DF
#define NEAT_QOS_AUDIO_M1                  NEAT_DSCP_EF
#define NEAT_QOS_AUDIO_H1                  NEAT_DSCP_EF
#define NEAT_QOS_INTERACTIVE_VIDEO_VL      NEAT_DSCP_CS1
#define NEAT_QOS_INTERACTIVE_VIDEO_L       NEAT_DSCP_DF
#define NEAT_QOS_INTERACTIVE_VIDEO_M1      NEAT_DSCP_AF42
#define NEAT_QOS_INTERACTIVE_VIDEO_M2      NEAT_DSCP_AF43
#define NEAT_QOS_INTERACTIVE_VIDEO_H1      NEAT_DSCP_AF41
#define NEAT_QOS_INTERACTIVE_VIDEO_H2      NEAT_DSCP_AF42
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_VL  NEAT_DSCP_CS1
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_L   NEAT_DSCP_DF
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_M1  NEAT_DSCP_AF32
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_M2  NEAT_DSCP_AF33
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_H1  NEAT_DSCP_AF31
#define NEAT_QOS_NON_INTERACTIVE_VIDEO_H2  NEAT_DSCP_AF32
#define NEAT_QOS_DATA_VL                   NEAT_DSCP_CS1
#define NEAT_QOS_DATA_L                    NEAT_DSCP_DF
#define NEAT_QOS_DATA_M1                   NEAT_DSCP_AF11
#define NEAT_QOS_DATA_H1                   NEAT_DSCP_AF21
#define NEAT_QOS_BROADCAST                 NEAT_DSCP_CS3
#define NEAT_QOS_REALTIME_INTERACTIVE_DATA NEAT_DSCP_CS4
#define NEAT_QOS_IMMERSIVE_AUDIO           NEAT_DSCP_AF41
#define NEAT_QOS_IMMERSIVE_VIDEO           NEAT_DSCP_AF41
#define NEAT_QOS_STREAMING                 NEAT_DSCP_AF31
#define NEAT_QOS_BACKGROUND                NEAT_DSCP_CS1
#define NEAT_QOS_BACKGROUND_SYSTEM         NEAT_DSCP_CS1
#define NEAT_QOS_ADMITTED_AUDIO            NEAT_DSCP_EF
#define NEAT_QOS_ADMITTED_VIDEO            NEAT_DSCP_AF42
#define NEAT_QOS_ADMITTED_IMMERSIVE_AUDIO  NEAT_DSCP_AF42
#define NEAT_QOS_ADMITTED_IMMERSIVE_VIDEO  NEAT_DSCP_AF42
#define NEAT_QOS_ADMITTED_DATA             NEAT_DSCP_AF42

#endif //NEAT_QOS_H
