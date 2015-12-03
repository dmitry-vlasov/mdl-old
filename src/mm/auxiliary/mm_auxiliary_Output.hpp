/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Output.hpp                                  */
/* Description:     class for output routines                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AUXILIARY_OUTPUT_HPP_
#define MM_AUXILIARY_OUTPUT_HPP_

#include "auxiliary/mm_auxiliary.dpp"
#include "interface/object/mm_interface_object_Object.hpp"

namespace mm {
namespace auxiliary {

class Output :
	public object :: Object,
	public Scalar<Output> {
public :
	Output (const String&);
	virtual ~ Output();

	void open ();
	void close ();
	String& buffer();
	void write (const object :: Writable* const);

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume () const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef Size_t Count;

	OutputFileStream fileStream_;
	String filePath_;
	String buffer_;
	Count objectCount_;

	enum {
		OUTPUT_FILE_FLUSH_COUNT_THRESHOLD = 32, // 32,
		INITIAL_OUTPUT_BUFFER_CAPACITY = 1024 * 64
	};
};

}
}

#endif /*MM_AUXILIARY_OUTPUT_HPP_*/
