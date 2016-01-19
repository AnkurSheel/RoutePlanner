// *****************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************

#include "ObjModelLoader.hxx"

namespace Graphics
{
	struct stTexVertex;
	struct stModelDef;
}

namespace Graphics
{
	class cObjModelLoader
		: public IObjModelLoader
	{
	private:
		///< Map of Model definitions. The key is the hash of the model filename. Value is a shared_ptr to the actual model def.
		typedef std::map<unsigned long, shared_ptr <stModelDef> > ModelDefMap;

	public:
		cObjModelLoader();

	private:
		~cObjModelLoader();
		shared_ptr<stModelDef> VGetModelDef(const Base::cString & strModelFile);
		////////////////////////////////////////////////////////////////////////
		/// Parses the strModelFile and loads the model in pModel
		/// @param[in] strModelFile The path of the model file
		/// @return The model
		///
		////////////////////////////////////////////////////////////////////////
		shared_ptr<stModelDef> LoadModelDef(const Base::cString & strModelFile);
		////////////////////////////////////////////////////////////////////////
		/// Parses the string value and returns it as a float. If the value is
		/// invalid returns 0.
		///
		/// @param[in] strVal The value as a string
		/// @return The value as a float
		////////////////////////////////////////////////////////////////////////
		float GetFloatValue(const Base::cString & strVal);
		////////////////////////////////////////////////////////////////////////
		/// Parses the string value and returns it as a int. If the value is 
		/// invalid returns 0.
		///
		/// @param[in] strVal The value as a string
		/// @return The value as a int
		////////////////////////////////////////////////////////////////////////
		int GetIntValue(const Base::cString & strVal);
		////////////////////////////////////////////////////////////////////////
		/// Checks if the model def has already been loaded. Returns a pointer 
		/// to the model def if it is found. NULL otherwise.
		///
		/// @param[in] ulModelDefHash The hash of the name of the model def name
		/// @return Pointer to the model def if it is found in the model def map.
		/// NULL otherwise
		////////////////////////////////////////////////////////////////////////
		shared_ptr<stModelDef> Find(const unsigned long ulModelDefHash);
		void Cleanup();

	private:
		ModelDefMap					m_pModelDefMap;	///< map of the model definitions that have already been loaded
		static IObjModelLoader *	s_pModelLoader;	///< static object of this class

	private:
		friend static IObjModelLoader * IObjModelLoader::GetInstance();
		friend static void IObjModelLoader::Destroy();
	};
}