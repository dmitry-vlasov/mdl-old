/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Output.hpp                                 */
/* Description:     output routines class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.dpp"

namespace del {
namespace auxiliary {

class Output :
	public nstd :: Object,
	public Scalar<Output> {
public :
	Output (const String&);
	virtual ~ Output();

	void open();
	void close();
	void write (const Writable* const);
	void flush();
	String& buffer();

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	typedef Size_t Count_;

	OutputFileStream fileStream_;
	String filePath_;
	String buffer_;
	Count_ objectCount_;

	enum {
		OUTPUT_FILE_FLUSH_COUNT_THRESHOLD = 32, //32,
		INITIAL_OUTPUT_BUFFER_CAPACITY = 1024 * 64
	};
};

}
}


