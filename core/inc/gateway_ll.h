// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/** @file		gateway_ll.h
*	@brief		Library that allows a user to create and configure a gateway.
*
*	@details	Gateway LL is the lower level library that allows a developer to 
*				create, configure, and manage a gateway. The library provides a 
*				mechanism for creating and destroying a gateway, as well as 
*				adding and removing modules. Developers looking for the high
*				level library should see gateway.h.
*/

#ifndef GATEWAY_LL_H
#define GATEWAY_LL_H

#include "azure_c_shared_utility/macro_utils.h"
#include "azure_c_shared_utility/vector.h"
#include "module.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @brief Struct representing a particular gateway. */
typedef struct GATEWAY_HANDLE_DATA_TAG* GATEWAY_HANDLE;

/** @brief Struct representing a single entry of the #GATEWAY_PROPERTIES. */
typedef struct GATEWAY_PROPERTIES_ENTRY_TAG
{
	/** @brief The (possibly @c NULL) name of the module */
	const char* module_name;
	
	/** @brief The path to the .dll or .so of the module */
	const char* module_path;
	
	/** @brief The user-defined configuration object for the module */
	const void* module_configuration;
} GATEWAY_PROPERTIES_ENTRY;

/** @brief	Struct representing the properties that should be used when 
			creating a module; each entry of the @c VECTOR_HANDLE being a 
*			#GATEWAY_PROPERTIES_ENTRY. 
*/
typedef struct GATEWAY_PROPERTIES_DATA_TAG
{
	/** @brief Vector of #GATEWAY_PROPERTIES_ENTRY objects. */
	VECTOR_HANDLE gateway_properties_entries;
} GATEWAY_PROPERTIES;

/** @brief  Enum representing different gateway events that have support for callbacks. */
typedef enum GATEWAY_EVENT_TAG
{
	GATEWAY_CREATED = 0,
	GATEWAY_DESTROYED,
	/* @brief  Not an actual event, used to keep track of count of different events */
	GATEWAY_EVENTS_COUNT
} GATEWAY_EVENT;

/** @brief  Placeholder for possible event context in the future. Right now NULL will be passed. */
typedef void* GATEWAY_EVENT_CTX;

/** @brief	Function pointer that can be registered and will be called for gateway events */
typedef void(*GATEWAY_CALLBACK)(GATEWAY_HANDLE gateway, GATEWAY_EVENT event_type, GATEWAY_EVENT_CTX context);

/** @brief		Creates a new gateway using the provided #GATEWAY_PROPERTIES.
*
*	@param		properties		#GATEWAY_PROPERTIES structure containing 
*								specific module properties and information.
*
*	@return		A non-NULL #GATEWAY_HANDLE that can be used to manage the 
*				gateway or @c NULL on failure.
*/
extern GATEWAY_HANDLE Gateway_LL_Create(const GATEWAY_PROPERTIES* properties);

/** @brief		Destroys the gateway and disposes of all associated data.
*
*	@param		gw		#GATEWAY_HANDLE to be destroyed.
*/
extern void Gateway_LL_Destroy(GATEWAY_HANDLE gw);

/** @brief		Creates a new module based on the GATEWAY_PROPERTIES_ENTRY*.
*
*	@param		gw		Pointer to a #GATEWAY_HANDLE to add the Module onto.
*	@param		entry	Pointer to a #GATEWAY_PROPERTIES_ENTRY structure
*						describing the module.
*
*	@return		A non-NULL #MODULE_HANDLE to the newly created and added
*				Module, or @c NULL on failure.
*/
extern MODULE_HANDLE Gateway_LL_AddModule(GATEWAY_HANDLE gw, const GATEWAY_PROPERTIES_ENTRY* entry);

/** @brief		Removes the provided module from the gateway.
*
*	@param		gw		Pointer to a #GATEWAY_HANDLE from which to remove the
*						Module.
*	@param		module	Pointer to a #MODULE_HANDLE that needs to be removed.
*/
extern void Gateway_LL_RemoveModule(GATEWAY_HANDLE gw, MODULE_HANDLE module);

/** @brief  Registers a function to be called on a callback thread when #GATEWAY_EVENT happens
*
*   @param  gw         Pointer to a #GATEWAY_HANDLE to which register callback to
*   @param  event_type Enum stating on which event should the callback be called
*   @param  callback   Pointer to a function that will be called when the event happens
*/
extern void Gateway_AddEventCallback(GATEWAY_HANDLE gw, GATEWAY_EVENT event_type, GATEWAY_CALLBACK callback);

#ifdef UWP_BINDING

/** @brief		Creates a new gateway using the provided #MODULEs and #MESSAGE_BUS_HANDLE.
*
*	@param		modules   		#VECTOR_HANDLE structure containing
*								specific modules.
*
*	@param		bus       		#MESSAGE_BUS_HANDLE structure containing
*								specific message bus.
*
*	@return		A non-NULL #GATEWAY_HANDLE that can be used to manage the
*				gateway or @c NULL on failure.
*/
extern GATEWAY_HANDLE Gateway_LL_UwpCreate(const VECTOR_HANDLE modules, MESSAGE_BUS_HANDLE bus);

/** @brief		Destroys the gateway and disposes of all associated data.
*
*	@param		gw		#GATEWAY_HANDLE to be destroyed.
*/
extern void Gateway_LL_UwpDestroy(GATEWAY_HANDLE gw);

#endif // UWP_BINDING

#ifdef __cplusplus
}
#endif

#endif // GATEWAY_LL_H
