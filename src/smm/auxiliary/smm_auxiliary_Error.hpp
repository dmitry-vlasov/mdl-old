/*****************************************************************************/
/* Project name:    smm - verifier for the Simplified MetaMath language      */
/* File name:       smm_auxiliary_Error.hpp                                  */
/* Description:     smm error exception class                                */
/* Copyright:       (c) 2006-2010 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef SMM_AUXILIARY_ERROR_HPP_
#define SMM_AUXILIARY_ERROR_HPP_

#include "smm/types/smm_types.hpp"
#include "smm/auxiliary/smm_auxiliary.dpp"

namespace smm {
namespace auxiliary {

class Error :
	public nstd :: Error<allocator :: Heap>,
	public Scalar<Error> {
public :
	enum Type_ {
		NONE         = 0,
		LEXER        = 1,
		PARSER       = 2,
		SEMANTIC     = 3,
		VERIFICATION = 4,
		INPUT        = 5
	};

	Error (const Location&, const Type_ type = NONE, const char* const = "");
	Error (const Type_ = NONE, const char* const = "");
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
	typedef
		nstd :: Error<allocator :: Heap>
		Ancestor_;

	Error (const Error&);

	const Type_ type_;
};

}
}

#endif /* SMM_AUXILIARY_ERROR_HPP_ */
