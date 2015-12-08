/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Tree.cpp                                 */
/* Description:     variant tree                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_TREE_CPP_
#define MDL_PROVER_TREE_TREE_CPP_

namespace mdl {
namespace prover {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	template<class A>
	Tree<A> :: Tree (Format& format, Format& subFormat, mdl :: proof :: Step* step) :
	format_ (format),
	subFormat_ (subFormat),
	timers_ (NULL),
	problem_ (step->getScope()->getAssertion()),
	hint_ (step),
	question_ (NULL),
	answer_ (NULL),
	scoping_ (step),
	premiseTree_ (NULL),
	premiseVector_ (NULL),
	expressionTree_ (NULL),
	variables_ (NULL),
	root_ (NULL),
	up_ (NULL),
	down_ (NULL),
	canGrowDown_ (false),
	mutex_ () {
		pthread_mutex_init (&mutex_, NULL);
	}
	template<class A>
	Tree<A> :: Tree (Format& format, Format& subFormat, mdl :: proof :: Question* question) :
	format_ (format),
	subFormat_ (subFormat),
	timers_ (NULL),
	problem_ (question->getScope()->getAssertion()),
	hint_ (question->getHint()),
	question_ (question),
	answer_ (NULL),
	scoping_ (question),
	premiseTree_ (NULL),
	premiseVector_ (NULL),
	expressionTree_ (NULL),
	variables_ (NULL),
	root_ (NULL),
	up_ (NULL),
	down_ (NULL),
	canGrowDown_ (true),
	mutex_() {
		pthread_mutex_init (&mutex_, NULL);
	}
	template<class A>
	Tree<A> :: ~ Tree()
	{
		object :: Object :: deleteAggregateObject (premiseTree_);
		object :: Object :: deleteAggregateObject (premiseVector_);
		object :: Object :: deleteAggregateObject (expressionTree_);
		object :: Object :: deleteAggregateObject (variables_);
		object :: Object :: deleteAggregateObject (timers_);
		object :: Object :: deleteAggregateObject (root_);
		object :: Object :: deleteAggregateObject (up_);
		object :: Object :: deleteAggregateObject (down_);
	}

using manipulator :: space;
using manipulator :: tab;
using manipulator :: endLine;
using manipulator :: iterate;
using manipulator :: mode;
using manipulator :: underline;

	// prover :: Tree implementation
	template<class A>
	bool
	Tree<A> :: prove (const Time timeLimit)
	{
		timers_->setLimit (timeLimit);
		timers_->start(); // death or glory!
		showStart (timeLimit);
		try {
			while (!timers_->timeIsOver() && !root_->isProved()) {
				if (!growUpDown() && !root_->isProved()) {
					format_.message() << "no way to go further";
					format_.showMessage();
					//showInGML();
					break;
				}
			}
		} catch (const OutOfMemory& outOfMemory) {
			format_.message() << outOfMemory.getMessage();
			format_.showMessage();
		}
		const mdl :: proof :: Step* answer = NULL;
		if (root_->isProved()) { // the proof is found, Glory!
			#ifdef DEBUG
			root_->verifyCompilation();
			#endif
			if ((Config :: verbosity() >= Config :: VERBOSE_MED) &&
				(timers_->wasRefreshed())) {
				showStatus();
			}
			if (Config :: verbosity() > Config :: VERBOSE_MED &&
				Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
				format_.message() << "proof ";
				question_->getScope()->getProof()->replicateName (format_.message());
				format_.message() << " was successfully proved in a determined way";
				format_.showMessage();
			}
			//show();
			//std :: cout << std :: endl << *answer << std :: endl;
		} else {
			showStatus();
		}
		//up_->getRoot()->dumpTree();
		timers_->stop(); // the battle is over ...
		showResult();

		verifyDeterminedGrowUp();
		verifyDeterminedGrowDown();

		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED &&
			Config :: growUpLimit() == 1 &&
			root_->getSize() > 1) {
			std :: cout << "MOAR THET 1 PROOF" << std :: endl;
		} else if (root_->getSize() == 0) {
			std :: cout << "NON PROOF GOT" << std :: endl;

			verifyDeterminedGrowUp();
			verifyDeterminedGrowDown();

			root_->dumpInvalidProofs();

			//up_->getRoot()->dumpTree (false, false);
			//up_->getRoot()->dumpTree (true, false);
			//up_->getRoot()->dumpTree (true, true);
		}
		//dumpVolume();
		return root_->isProved();
	}
	template<class A>
	void
	Tree<A> :: start (String& message)
	{
		if (Config :: growUpMode() != Config :: GROW_UP_DETERMINED) {
			message << "step " << question_->getIndex() + 1 << " in ";
			problem_->replicateName (message);
			message << " (" << problem_->getIndex() << "), ";
		}
	}
	template<class A>
	void
	Tree<A> :: grow()
	{
		if (Config :: growCompleteTree()) {
			while (growUpDown());
		} else {
			growUpDown();
		}
	}
	template<class A>
	void
	Tree<A> :: stop()
	{
		if (!isProved() && Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			format_.message() << "proof ";
			question_->getScope()->getProof()->replicateName (format_.message());
			format_.message() << " was NOT proved in a determined way";
			format_.showMessage();
		}
	}
	template<class A>
	void
	Tree<A> :: info (String& string)
	{
		// Printing the header.
		switch (Config :: showMode()) {
		case Config :: SHOW_MODE_HUMAN :
			break;
		case Config :: SHOW_MODE_XML :
			string << "<!DOCTYPE russell_proof_tree>" << endLine;
			break;
		case Config :: SHOW_MODE_GML :
			// TODO: implement
		default : break;
		}
		// Printing the main body.
		switch (Config :: infoTree()) {
		case Config :: SHOW_TREE_NODE :
			showNodeInfo (string); break;
		case Config :: SHOW_TREE_EVIDENCE :
			showEvidenceInfo (string); break;
		case Config :: SHOW_TREE_UP :
			showUpTreeInfo (string); break;
		case Config :: SHOW_TREE_DOWN :
			showDownTreeInfo (string); break;
		case Config :: SHOW_TREE :
			showTreeInfo (string); break;
		case Config :: SHOW_TREE_SPROUT :
			showSproutInfo (string); break;
		default :
			break;
		}
	}
	template<class A>
	void
	Tree<A> :: confirm()
	{
		const value :: Integer index = Config :: getInteger(Config :: INDEX);
		if (index == value :: undefined :: INTEGER) {
			answer_ = root_->takeBestProof();
		} else {
			answer_ = root_->takeProof (index);
		}
		question_->confirmAnswer (answer_);
	}
	template<class A>
	bool
	Tree<A> :: isProved() {
		return root_->isProved();
	}
	template<class A>
	void
	Tree<A> :: showVolume (String& string, const int indent) const
	{
		Data data (*this);
		data.showVolume (string, indent);
	}
	template<class A>
	void
	Tree<A> :: showTiming (String& string, const int indent) const
	{
		Data data (*this);
		data.showTiming (string, indent);
	}
	template<class A>
	Data*
	Tree<A> :: getData() const {
		return new Data (*this);
	}

	template<class A>
	void
	Tree<A> :: writeHeader (String& string, const char* header, const int indent)
	{
		string << iterate << indent << tab;
		switch (Config :: showMode()) {
		case Config :: SHOW_MODE_HUMAN :
			string << header << ":" << endLine; break;
		case Config :: SHOW_MODE_XML :
			string << "<" << header << ">" << endLine; break;
		case Config :: SHOW_MODE_GML :
			break; // TODO: implement
		default : break;
		}
	}
	template<class A>
	void
	Tree<A> :: writeEnding (String& string, const char* ending, const int indent)
	{
		string << iterate << indent << tab;
		switch (Config :: showMode()) {
		case Config :: SHOW_MODE_HUMAN :
			string << endLine; break;
		case Config :: SHOW_MODE_XML :
			string << "</" << ending << ">" << endLine; break;
		case Config :: SHOW_MODE_GML :
			break; // TODO: implement
		default : break;
		}
	}

	template<class A>
	void
	Tree<A> :: verifyDeterminedGrowUp()
	{
		if (Config :: growUpMode() != Config :: GROW_UP_DETERMINED) {
			return;
		}
		const Node_* root = up_->getRoot();
		const value :: Integer propHintCount = root->countPropHintNodes();
		const value :: Integer proofHintSize = hint_->getScope()->getProof()->getLength();
		if (Config :: growUpLimit() == 1) {
			if (propHintCount != proofHintSize) {
				std :: cout << "hint prop node count differs from the proof size:" << std :: endl;
				std :: cout << "-------------------------------------------------" << std :: endl;
				std :: cout << "\thint count = " << propHintCount << std :: endl;
				std :: cout << "\tproof size = " << proofHintSize << std :: endl;
				//root->dumpTree();
			}
		} else {
			if (propHintCount < proofHintSize) {
				if (isProved()) {
					// The case, when another (shorter) proof was found
					return;
				}
				std :: cout << "hint prop node count is less then the proof size:" << std :: endl;
				std :: cout << "-------------------------------------------------" << std :: endl;
				std :: cout << "\thint count = " << propHintCount << std :: endl;
				std :: cout << "\tproof size = " << proofHintSize << std :: endl;
				//root->dumpTree();
			}
		}
	}
	template<class A>
	void
	Tree<A> :: verifyDeterminedGrowDown()
	{
		if (Config :: growUpMode() != Config :: GROW_UP_DETERMINED) {
			return;
		}
		typedef
			typename vector :: Vector
			<
				Node_*,
				storage :: ByValue,
				allocator :: Standard
			>
			NodeVector_;
		NodeVector_ unprovedNodes;
		Node_* root = up_->getRoot();
		root->findUnprovedHintNodes (unprovedNodes);
		if (unprovedNodes.getSize() == 0) {
			return;
		}
		if (isProved()) {
			// The case, when another (shorter) proof was found
			return;
		}
		std :: cout << "some nodes are not proved at determined grow up." << std :: endl;
		std :: cout << "------------------------------------------------" << std :: endl;
		//root->dumpTree();
		typedef
			typename Types_ :: Evidences_
			Evidences;
		value :: Integer minMatrixSize = value :: undefined :: INTEGER;
		value :: Integer maxMatrixSize = 0;
		value :: Integer minIndex = value :: undefined :: INTEGER;
		for (int i = 0; i < unprovedNodes.getSize(); ++ i) {
			Node_* unproved = unprovedNodes.getValue (i);

			std :: cout << "unproved node:" << std :: endl;
			unproved->dumpTree (true, true, 2);

			//Counter :: set ();
			//unproved->growDown (NULL);
			//Counter :: set (1000);

			value :: Integer matrixSize = 1;
			for (index :: Arity j = 0; j < unproved->getUpArity(); ++ j) {
				const Node_* unprovedUp = unproved->getUp (j);
				const Evidences& evidences = unprovedUp->getEvidences();
				matrixSize *= evidences.getSize();
			}
			if (matrixSize < minMatrixSize) {
				minMatrixSize = matrixSize;
				minIndex = i;
			}
			if (matrixSize > maxMatrixSize) {
				maxMatrixSize = matrixSize;
			}
		}

		std :: cout << "unproved statistics" << std :: endl;
		std :: cout << "-------------------" << std :: endl;
		std :: cout << "\tunproved count = " << unprovedNodes.getSize() << std :: endl;
		std :: cout << "\tmax matrix size = " << maxMatrixSize << std :: endl;
		std :: cout << "\tmin matrix size = " << maxMatrixSize << std :: endl;
	}


	template<class A>
	void
	Tree<A> :: init()
	{
		if (timers_ != NULL) {
			return;
		}
		timers_ = new Timers();
		premiseTree_ = new PremiseTree_();
		premiseVector_ = new PremiseVector_ (INITIAL_PREMISE_VECTOR_CAPACITY);
		expressionTree_ = new ExpressionTree_();
		variables_ = new Variables_ (INITIAL_VARIABLES_CAPACITY);
		root_ = new Root_ (this);
		up_ = new UpTree_ (this);
		down_ = new DownTree_ (this, root_);

		arrangePremises();
		Expression_* expression = new Expression_ (question_->getExpression());
		up_->createRoot (expression, hint_);
	}

	template<class A>
	void
	Tree<A> :: growUpForLearning (const Time timeLimit, const value :: Integer sizeLimit)
	{
		timers_->setLimit (timeLimit);
		timers_->start();
		down_->block();
		try {
			up_->crown_->setMode (UpTree_ :: Crown_ :: RESTRICT_TO_HINTS);
			while (up_->crown_->grow()) {
			}
			up_->removeNonHintLevels();
			up_->crown_->setMode (UpTree_ :: Crown_ :: RESTRICT_HEIGHT);
			while (!timers_->timeIsOver()) {
				if (!up_->crown_->grow()) {
					break;
				}
				if (up_->getExpressionVolume() > sizeLimit) {
					break;
				}
			}
		} catch (const OutOfMemory& outOfMemory) {
			format_.message() << outOfMemory.getMessage();
			format_.showMessage();
		}
		down_->unblock();
		timers_->stop();
	}

	template<class A>
	inline typename Tree<A> :: Root_&
	Tree<A> :: root() {
		return *root_;
	}
	template<class A>
	inline typename Tree<A> :: UpTree_&
	Tree<A> :: up() {
		return *up_;
	}
	template<class A>
	inline typename Tree<A> :: DownTree_&
	Tree<A> :: down() {
		return *down_;
	}

	template<class A>
	inline bool
	Tree<A> :: canGrowDown() const {
		return canGrowDown_;
	}

	template<class A>
	inline value :: Real
	Tree<A> :: evalFitness() const {
		return up_->evalFitness();
	}

	template<class A>
	inline const mdl :: Assertion*
	Tree<A> :: getProblem() const {
		return problem_;
	}
	template<class A>
	inline const typename Tree<A> :: PremiseTree_*
	Tree<A> :: getPremiseTree() const {
		return premiseTree_;
	}
	template<class A>
	inline const typename Tree<A> :: PremiseVector_*
	Tree<A> :: getPremiseVector() const {
		return premiseVector_;
	}
	template<class A>
	inline index :: Assertion
	Tree<A> :: getProblemIndex()
	{
		const mdl :: Proposition*
			firstProposition = problem_->getProposition (0);
		const index :: Assertion
			problemIndex = firstProposition->getSourceIndex();
		return problemIndex;
	}
	template<class A>
	inline index :: Step
	Tree<A> :: getStepBoundary() {
		return question_->getIndex() + problem_->getHypArity();
	}
	template<class A>
	inline const mdl :: proof :: Question*
	Tree<A> :: getQuestion() const {
		return question_;
	}
	template<class A>
	inline mdl :: proof :: Question*
	Tree<A> :: getQuestion() {
		return question_;
	}
	template<class A>
	Symbol
	Tree<A> :: createVariable (const Symbol& symbol)
	{
		pthread_mutex_lock (&mutex_);
		Symbol newSymbol (symbol);
		value :: Integer
			counter = variables_->addFind (symbol.getLiteral(), 0);

		Memory :: stack().push();
		nstd :: String<allocator :: Stack> string (64);
		const String&
			originalString = Table :: literals()->get (symbol.getLiteral());
		while (true) {
			++ counter; string.clear();
			string << originalString << underline << counter;
			const value :: Literal
				literal = Table :: literals()->add (string);
			if (scoping_->getScope()->getVariables()->getType (literal) == NULL) {
				newSymbol.setLiteral (literal);
				variables_->set (symbol.getLiteral(), counter);
				break;
			}
		}
		Memory :: stack().pop();
		pthread_mutex_unlock (&mutex_);
		return newSymbol;
	}

	template<class A>
	inline void
	Tree<A> :: refresh (const char* message, const bool force) const
	{
		if (force || timers_->refresh()) {
			//showStatus (message);
			showStatus();
		}
	}
	template<class A>
	inline const Timers*
	Tree<A> :: getTimers() const {
		return timers_;
	}
	template<class A>
	inline Timers*
	Tree<A> :: getTimers() {
		return timers_;
	}
	template<class A>
	void
	Tree<A> :: showInGML() const
	{
		String& string = Engine :: get()->log().message (Log :: GRAPH);
		Mode m;
		m.setValue (Mode :: SHOW_IN_GML_GRAPH);
		//m.setValue (Mode :: SHOW_IN_GML_NODE);
		m.setValue (Mode :: SHOW_IN_GML_EVIDENCE);
		m.setValue (Mode :: SHOW_ONLY_HINT);

		m.setValue (Mode :: SHOW_IN_GML_EXPRESSION);
		m.setValue (Mode :: SHOW_IN_GML_ASSERTION);
		m.setValue (Mode :: SHOW_IN_GML_WEIGHT);
		//m.setValue (Mode :: SHOW_IN_GML_ADDRESS);
		//m.setValue (Mode :: SHOW_IN_GML_HEIGHT_MIN);
		//m.setValue (Mode :: SHOW_IN_GML_HEIGHT_MAX);
		//m.setValue (Mode :: SHOW_IN_GML_SUBSTITUTION);

		string << mode << m;
		show (string);
			Engine :: get()->log().write (Log :: GRAPH);
	}
	template<class A>
	void
	Tree<A> :: showInGML (const String& fileName) const
	{
		Engine :: get()->log().setName (Log :: GRAPH, fileName);
		String& string = Engine :: get()->log().message (Log :: GRAPH);
		Mode m;
		m.setValue (Mode :: SHOW_IN_GML_GRAPH);
		m.setValue (Mode :: SHOW_IN_GML_NODE);
		//m.setValue (Mode :: SHOW_IN_GML_EVIDENCE);

		m.setValue (Mode :: SHOW_IN_GML_EXPRESSION);
		m.setValue (Mode :: SHOW_IN_GML_ASSERTION);
		m.setValue (Mode :: SHOW_IN_GML_WEIGHT);
		//m.setValue (Mode :: SHOW_IN_GML_ADDRESS);
		//m.setValue (Mode :: SHOW_IN_GML_HEIGHT_MIN);
		//m.setValue (Mode :: SHOW_IN_GML_HEIGHT_MAX);
		//m.setValue (Mode :: SHOW_IN_GML_SUBSTITUTION);

		string << mode << m;
		show (string);
		Engine :: get()->log().write (Log :: GRAPH);
	}


	// object :: Object implementation
	template<class A>
	void
	Tree<A> :: commitSuicide() {
		delete this;
	}
	template<class A>
	Size_t
	Tree<A> :: getVolume() const
	{
		Size_t volume = 0;
		volume += object :: Object :: getAggregateVolume (premiseTree_);
		volume += object :: Object :: getAggregateVolume (premiseVector_);
		volume += object :: Object :: getAggregateVolume (expressionTree_);
		volume += object :: Object :: getAggregateVolume (variables_);
		volume += object :: Object :: getAggregateVolume (timers_);
		volume += object :: Object :: getAggregateVolume (root_);
		volume += object :: Object :: getAggregateVolume (up_);
		volume += object :: Object :: getAggregateVolume (down_);
		return volume;
	}
	template<class A>
	Size_t
	Tree<A> :: getSizeOf() const {
		return sizeof (Tree);
	}
	template<class A>
	void
	Tree<A> :: show (String& string) const
	{
		up_->show (string);
		down_->show (string);
	}

	/****************************
	 *		Private members
	 ****************************/

	template<class A>
	inline bool
	Tree<A> :: growUpDown()
	{
		timers_->growUp().start();
		bool successUp = up_->grow();
		timers_->growUp().stop();

		timers_->growDown().start();
		bool successDown = false;
		if (canGrowDown_) {
			//while (down_->grow());
			successDown = down_->grow();
		}
		timers_->growDown().stop();

		return (successUp || successDown);
	}
	template<class A>
	inline void
	Tree<A> :: arrangePremises()
	{
		addLinePremises();
		if (!addClaimPremises()) {
			addAssertionPremises();
		}
	}
	template<class A>
	void
	Tree<A> :: addLinePremises()
	{
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			return;
		}
		mdl :: proof :: Line* line = question_->getPrev();
		if (line == NULL) {
			return;
		}
		while (true) {
			mdl :: proof :: Node*
				node = dynamic_cast<mdl :: proof :: Node*>(line);
			if (node != NULL) {
				array :: Expression*
					expression = node->getExpression();
				premiseVector_->add (node);
				premiseTree_->addBranch (expression, node);
			}
			if (line->getPrev() != NULL) {
				line = line->getPrev();
			} else {
				break;
			}
		}
	}
	template<class A>
	bool
	Tree<A> :: addClaimPremises()
	{
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			return false;
		}
		mdl :: proof :: Claim*
			claim = question_->getScope()->getClaim();
		if (claim != NULL) {
			mdl :: proof :: Link*
				link = claim->getLink();
			for (index :: Arity i = 0; i < link->getReferences()->getArity(); ++ i) {
				mdl :: proof :: Node*
					node = link->getReferences()->get (i)->getNode();
				premiseVector_->add (node);
				premiseTree_->addBranch (node->getExpression(), node);
			}
			return true;
		} else {
			return false;
		}
	}
	template<class A>
	void
	Tree<A> :: addAssertionPremises()
	{
		mdl :: Assertion*
			assertion = question_->getScope()->getAssertion();
		for (index :: Arity i = 0; i < assertion->getHypArity(); ++ i) {
			mdl :: Hypothesis*
				hypothesis = assertion->getHypothesis (i);
			mdl :: proof :: Node*
				node = hypothesis->getProofNode();
			premiseVector_->add (node);
			premiseTree_->addBranch (node->getExpression(), node);
		}
	}

	template<class A>
	void
	Tree<A> :: showStart (const Time timeLimit) const
	{
		if (Config :: verbosity() < Config :: VERBOSE_MED) {
			return;
		}
		String message (INITIAL_MESSAGE_CAPACITY);
		message << "proving ";
		message << "step " << question_->getIndex() + 1 << " in ";
		problem_->replicateName (message);
		message << " (" << problem_->getIndex() << "), ";
		message << "time limit = " << timeLimit << "s ";
		message << "...";
		//Engine :: get()->log().message(Log :: PROVER) << string;
		format_.message() << message;
		format_.showMessage();
	}
	template<class A>
	void
	Tree<A> :: showResult() const
	{
		if (Config :: verbosity() < Config :: VERBOSE_MED) {
			return;
		}
		String message (INITIAL_MESSAGE_CAPACITY);
		if (root_->isProved()) {
			message << "done in " << timers_->prove();
			message << ".";
		} else {
			message << "failed.";
		}
		format_.message() << message;
		format_.showMessage();
		//Engine :: get()->log().message (Log :: PROVER) << string;
	}
	template<class A>
	void
	Tree<A> :: showStatus (const char* string) const
	{
		if (Config :: verbosity() < Config :: VERBOSE_MED) {
			return;
		}
		Mode m;
		//m.setValue (Mode :: END_LINE);

		m.setValue (Mode :: SHOW_TREE_STATISTICS);
		m.setValue (Mode :: SHOW_UP_TREE_CARD);
		//m.setValue (Mode :: SHOW_UP_CROWN_CARD);
		m.setValue (Mode :: SHOW_UP_TREE_VOLUME);
		//m.setValue (Mode :: SHOW_UP_CROWN_H_MIN);
		//m.setValue (Mode :: SHOW_UP_CROWN_H_MAX);

		m.setValue (Mode :: SHOW_DOWN_TREE_CARD);
		m.setValue (Mode :: SHOW_DOWN_TREE_VOLUME);
		//m.setValue (Mode :: SHOW_DOWN_ROOT_CARD);
		//m.setValue (Mode :: SHOW_DOWN_CROWN_CARD);

		//m.setValue (Mode :: SHOW_USED_VOLUME);
		//m.setValue (Mode :: SHOW_HINT_STAT);
		//m.setValue (Mode :: SHOW_TREE_VOLUME);
		//m.setValue (Mode :: SHOW_GROW_UP_VELOCITY);
		//m.setValue (Mode :: SHOW_GROW_DOWN_VELOCITY);
		//m.setValue (Mode :: SHOW_EXPRESSION_VOLUME);
		//m.setValue (Mode :: SHOW_NEW_VARIABLES_VOLUME);

		//m.setValue (Mode :: SHOW_UP_TREE_FITNESS);
		//m.setValue (Mode :: SHOW_UP_TREE_PARTITION);

		//m.setValue (Mode :: SHOW_FULL_DESCRIPTION);

		String message (INITIAL_MESSAGE_CAPACITY);
		message << mode << m;

		if (Config :: verbosity() >= Config :: VERBOSE_MED) {
			//message << space << endLine << tab;
			if (string != "") {
				message << "[" << string << "]" << space;
			}
			message << *timers_;
			show (message);
		}
		//Engine :: get()->log().message(Log :: PROVER) << string;
		format_.message() << message;
		format_.showMessage();
	}

	template<class A>
	void
	Tree<A> :: showNodeInfo (String& string) const
	{
		const char* header = "node";
		writeHeader (string, header);
		const value :: Integer index = Config :: getInteger(Config :: INDEX);
		if (index == value :: undefined :: INTEGER) {
			return;
		}
		const Node_* node = up_->getNode (index);
		node->showInfo (string, 1);
		writeEnding (string, header);
	}
	template<class A>
	void
	Tree<A> :: showEvidenceInfo (String& string) const
	{
		const char* header = "evidence";
		writeHeader (string, header);
		const value :: Integer index = Config :: getInteger(Config :: INDEX);
		if (index == value :: undefined :: INTEGER) {
			return;
		}
		const Evidence_* evidence = down_->getEvidence (index);
		evidence->showInfo (string, 1);
		writeEnding (string, header);
	}
	template<class A>
	void
	Tree<A> :: showUpTreeInfo (String& string) const
	{
		const char* header = "up_tree";
		writeHeader (string, header);
		up_->showInfo (string);
		writeEnding (string, header);
	}
	template<class A>
	void
	Tree<A> :: showDownTreeInfo (String& string) const
	{
		const char* header = "up_tree";
		writeHeader (string, header);
		up_->showInfo (string);
		writeEnding (string, header);
	}
	template<class A>
	void
	Tree<A> :: showTreeInfo (String& string) const
	{
		const char* header = "tree";
		writeHeader (string, header);
		writeEnding (string, header);
	}
	template<class A>
	void
	Tree<A> :: showSproutInfo (String& string) const
	{
		const char* header = "sprout";
		writeHeader (string, header);
		up_->showInfo (string, 1);
		if (root_ != NULL) {
			root_->showInfo (string, 1);
		}
		writeEnding (string, header);
	}
}
}
}

#endif /*MDL_PROVER_TREE_TREE_CPP_*/
