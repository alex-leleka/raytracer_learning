#pragma once

//#define BHV_NODE_VISUAL_DEBUG

#ifdef BHV_NODE_VISUAL_DEBUG
#define BHV_NODE_VISUAL_DEBUG_FIELD_NAME .bhv_depth
#define BHV_NODE_VISUAL_DEBUG_FIELD int bhv_depth {0};
#define BHV_NODE_VISUAL_DEBUG_INCREMENT .bhv_depth++
#else
#define BHV_NODE_VISUAL_DEBUG_FIELD_NAME
#define BHV_NODE_VISUAL_DEBUG_FIELD 
#define BHV_NODE_VISUAL_DEBUG_INCREMENT
#endif