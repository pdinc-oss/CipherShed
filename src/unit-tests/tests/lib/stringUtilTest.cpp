#include "../../unittesting.h"

#include "../../../Common/util/csstringutil.h"
#include <stdlib.h>

namespace CipherShed_Tests_lib
{
	typedef struct TS_UpperCaseCopy
	{
		char* src;
		char* dst;
		int r;
	} TS_UpperCaseCopy;

	static TS_UpperCaseCopy testDataTS_UpperCaseCopy[]=
	{
		{"xyzzy",      "XYZZY",      0},
		{"",           "",           0},
		{"a",          "A",          0},
		{"A",          "A",          0},
		{"abc",        "ABC",        0},
	};

	TESTCLASS
	PUBLIC_REF_CLASS StringUtilTest TESTCLASSEXTENDS
	{
	private:
		TESTCONTEXT testContextInstance;

	public: 
		TESTCONTEXTPROP

		#pragma region Additional test attributes
		#pragma endregion 

		/**
		The each test method needs this decoration for the VS unit test execution.
		*/
		TESTMETHOD
		void testStringUtilTrue()
		{
			TEST_ASSERT(1==1);
		};

		TESTMETHOD
		void testStringUtilCopyUpper()
		{
			char buf[2048];
			for (int i=0; i<sizeof(testDataTS_UpperCaseCopy)/sizeof(testDataTS_UpperCaseCopy[0]); ++i)
			{
				for (int ii=0; ii<sizeof(buf)/sizeof(buf[0]); ++ii) buf[ii]=0;

				UpperCaseCopy (buf, testDataTS_UpperCaseCopy[i].src);
				int c=strcmp(testDataTS_UpperCaseCopy[i].src,buf);

				int l=strlen(buf);

				char msg[2048];
				sprintf(msg,"i:%d test str <%s> expected:<%s> with strcmp=%d, got <%s> with strcmp=%d and strlen=%d",i,testDataTS_UpperCaseCopy[i].src, testDataTS_UpperCaseCopy[i].dst,testDataTS_UpperCaseCopy[i].r, buf, c, l);
				TEST_ASSERT_MSG(c==testDataTS_UpperCaseCopy[i].r,msg);
			}

		};

		TESTMETHOD
		void testStringUtilStdLibToUpper()
		{
			char a='a';
			char A='A';

			char t=toupper(a);

			char msg[2048];
			sprintf(msg,"l=%c, u=%c, t=%c",a,A,t);
			TEST_ASSERT_MSG(A==t,msg);

		};


		TESTMETHOD
		void testStringUtilStdLibStrlen()
		{
			char* strs[]={"","a","aa","aaa"};

			for (int i=0; i<sizeof(strs)/sizeof(strs[0]); ++i)
			{
				int l=strlen(strs[i]);
				TEST_ASSERT_MSG(i==l,strs[i]);
			}
		};


		/**
		The constructor needs the add each test method for the non-VS unit test execution.
		*/
		StringUtilTest()
		{
			TEST_ADD(StringUtilTest::testStringUtilStdLibToUpper);
			TEST_ADD(StringUtilTest::testStringUtilTrue);
		}
	};
}
