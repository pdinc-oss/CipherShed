/*
 Copyright (c) 2008 TrueCrypt Developers Association. All rights reserved.

 Governed by the TrueCrypt License 3.0 the full text of which is contained in
 the file License.txt included in TrueCrypt binary and source code distribution
 packages.
*/

#ifndef TC_HEADER_Platform_Serializable
#define TC_HEADER_Platform_Serializable
/*
#include <stdexcept>
#include "PlatformBase.h"
using namespace std;
#include "ForEach.h"
#include "Serializer.h"
#include "SerializerFactory.h"
#include <typeinfo>
*/

#include <memory>
#include "Stream.h"
#include <list>
#include "Serializer.h"

namespace CipherShed
{
	class Serializable
	{
	public:
		virtual ~Serializable () { }

		virtual void Deserialize (std::tr1::shared_ptr <Stream> stream) = 0;
		static string DeserializeHeader (std::tr1::shared_ptr <Stream> stream);
		static Serializable *DeserializeNew (std::tr1::shared_ptr <Stream> stream);
		
		template <class T> 
		static std::tr1::shared_ptr <T> DeserializeNew (std::tr1::shared_ptr <Stream> stream)
		{
			std::tr1::shared_ptr <T> p (dynamic_cast <T *> (DeserializeNew (stream)));
			if (!p)
				throw std::runtime_error (SRC_POS);
			return p;
		}

		template <class T> 
		static void DeserializeList (std::tr1::shared_ptr <Stream> stream, list < std::tr1::shared_ptr <T> > &dataList)
		{
			if (DeserializeHeader (stream) != string ("list<") + SerializerFactory::GetName (typeid (T)) + ">")
				throw std::runtime_error (SRC_POS);

			Serializer sr (stream);
			uint64 listSize;
			sr.Deserialize ("ListSize", listSize);

			for (size_t i = 0; i < listSize; i++)
			{
				std::tr1::shared_ptr <T> p (dynamic_cast <T *> (DeserializeNew (stream)));
				if (!p)
					throw std::runtime_error (SRC_POS);
				dataList.push_back (p);
			}
		}

		virtual void Serialize (std::tr1::shared_ptr <Stream> stream) const;

		template <class T>
		static void SerializeList (std::tr1::shared_ptr <Stream> stream, const list < std::tr1::shared_ptr <T> > &dataList)
		{
			Serializer sr (stream);
			SerializeHeader (sr, string ("list<") + SerializerFactory::GetName (typeid (T)) + ">");

			sr.Serialize ("ListSize", (uint64) dataList.size());
			foreach_ref (const T &item, dataList)
				item.Serialize (stream);
		}

		static void SerializeHeader (Serializer &serializer, const string &name);

	protected:
		Serializable () { }
	};
}

#define TC_SERIALIZABLE(TYPE) \
	static Serializable *GetNewSerializable () { return new TYPE(); } \
	virtual void Deserialize (std::tr1::shared_ptr <Stream> stream); \
	virtual void Serialize (std::tr1::shared_ptr <Stream> stream) const

#endif // TC_HEADER_Platform_Serializable
