/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File name:       del_auxiliary_Error.hpp                                  */
/* Description:     error exception class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_AUXILIARY_ERROR_HPP_
#define DEL_AUXILIARY_ERROR_HPP_

#include "del/types/del_types.hpp"

namespace del {
namespace auxiliary {

class Error :
	public nstd :: Error<allocator :: Heap>,
	public Scalar<Error, allocator :: Heap> {
public :
	enum Type_ {
		NONE     = 0,
		LEXER    = 1,
		PARSER   = 2,
		SEMANTIC = 3,
		INPUT    = 4,
		OUTPUT   = 5
	};

	Error (const Location&, const Type_ type = NONE, const char* const = "");
	Error (const Type_ type = NONE, const char* const = "");
	virtual ~ Error() throw();

	Type_ getType() const;

	// nstd :: Error interface
	Message_& message();
	void add (const Location_&, const char* = "");
	const char* what() const throw();
	void showMessage (Message_&) const;

	// nstd :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (nstd :: String<>&) const;

private :
	typedef nstd :: Error<allocator :: Heap> Ancestor_;
	Error (const Error& error);
	const Type_ type_;
};

}
}

#endif /* DEL_AUXILIARY_ERROR_HPP_ */
