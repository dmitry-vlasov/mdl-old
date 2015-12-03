$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Pre-logic
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

  $( Declare the primitive constant symbols for propositional calculus. $)
  $c ( $.  $( Left parenthesis $)
  $c ) $.  $( Right parenthesis $)
  $c -> $. $( Right arrow (read:  "implies") $)
  $c -. $. $( Right handle (read:  "not") $)
  $c wff $. $( Well-formed formula symbol (read:  "the following symbol
               sequence is a wff") $)
  $c |- $. $( Turnstile (read:  "the following symbol sequence is provable" or
              'a proof exists for") $)

  $( Introduce some variable names we will use to represent well-formed
     formulas (wff's). $)
  $v ph $. $( Greek phi $)
  $v ps $.  $( Greek psi $)
  $v ch $.  $( Greek chi $)
  $v th $.  $( Greek theta $)
  $v ta $.  $( Greek tau $)

  $( Specify some variables that we will use to represent wff's.
     The fact that a variable represents a wff is relevant only to a theorem
     referring to that variable, so we may use $f hypotheses.  The symbol
     ` wff ` specifies that the variable that follows it represents a wff. $)
  $( Let variable ` ph ` be a wff. $)
  wph $f wff ph $.
  $( Let variable ` ps ` be a wff. $)
  wps $f wff ps $.
  $( Let variable ` ch ` be a wff. $)
  wch $f wff ch $.
  $( Let variable ` th ` be a wff. $)
  wth $f wff th $.
  $( Let variable ` ta ` be a wff. $)
  wta $f wff ta $.

$(
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
                           Propositional calculus
#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#
$)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Recursively define primitive wffs for propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $( If ` ph ` is a wff, so is ` -. ph ` or "not ` ph ` ."  Part of the
     recursive definition of a wff (well-formed formula).  In classical logic
     (which is our logic), a wff is interpreted as either true or false.
     So if ` ph ` is true, then ` -. ph ` is false; if ` ph ` is false, then
     ` -. ph ` is true.  Traditionally, Greek letters are used to represent
     wffs, and we follow this convention.  In propositional calculus, we define
     only wffs built up from other wffs, i.e. there is no starting or "atomic"
     wff.  Later, in predicate calculus, we will extend the basic wff
     definition by including atomic wffs ( ~ weq and ~ wel ). $)
  wn $a wff -. ph $.

  $( If ` ph ` and ` ps ` are wff's, so is ` ( ph -> ps ) ` or " ` ph ` implies
     ` ps ` ."  Part of the recursive definition of a wff.  The resulting wff
     is (interpreted as) false when ` ph ` is true and ` ps ` is false; it is
     true otherwise.  (Think of the truth table for an OR gate with input
     ` ph ` connected through an inverter.)  The left-hand wff is called the
     antecedent, and the right-hand wff is called the consequent.  In the case
     of ` ( ph -> ( ps -> ch ) ) ` , the middle ` ps ` may be informally called
     either an antecedent or part of the consequent depending on context. $)
  wi $a wff ( ph -> ps ) $.

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        The axioms of propositional calculus
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

  $(
     Postulate the three axioms of classical propositional calculus.
  $)

  $( Axiom _Simp_.  Axiom A1 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  The 3 axioms are also given as Definition 2.1
     of [Hamilton] p. 28.  This axiom is called _Simp_ or "the principle of
     simplification" in _Principia Mathematica_ (Theorem *2.02 of
     [WhiteheadRussell] p. 100) because "it enables us to pass from the joint
     assertion of ` ph ` and ` ps ` to the assertion of ` ph ` simply."

     _General remarks_:  Propositional calculus (axioms ~ ax-1 through ~ ax-3
     and rule ~ ax-mp ) can be thought of as asserting formulas that are
     universally "true" when their variables are replaced by any combination
     of "true" and "false."  Propositional calculus was first formalized by
     Frege in 1879, using as his axioms (in addition to rule ~ ax-mp ) the
     wffs ~ ax-1 , ~ ax-2 , ~ pm2.04 , ~ con3 , ~ nega , and ~ negb .  Around
     1930, Lukasiewicz simplified the system by eliminating the third (which
     follows from the first two, as you can see by looking at the proof of
     ~ pm2.04 ) and replacing the last three with our ~ ax-3 .  (Thanks to Ted
     Ulrich for this information.)

     The theorems of propositional calculus are also called _tautologies_.
     Tautologies can be proved very simply using truth tables, based on the
     true/false interpretation of propositional calculus.  To do this, we
     assign all possible combinations of true and false to the wff variables
     and verify that the result (using the rules described in ~ wi and ~ wn )
     always evaluates to true.  This is called the _semantic_ approach.  Our
     approach is called the _syntactic_ approach, in which everything is
     derived from axioms.  A metatheorem called the Completeness Theorem for
     Propositional Calculus shows that the two approaches are equivalent and
     even provides an algorithm for automatically generating syntactic proofs
     from a truth table.  Those proofs, however, tend to be long, and the
     much shorter proofs that we show here were found manually.  Truth tables
     grow exponentially with the number of variables, but it is unknown if the
     same is true of proofs - an answer to this would resolve the P=NP
     conjecture in complexity theory. $)
  ax-1 $a |- ( ph -> ( ps -> ph ) ) $.
  $( [ ?] $) $( [ ?] $)

  $( Axiom _Frege_.  Axiom A2 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It "distributes" an antecedent over two
     consequents.  This axiom was part of Frege's original system and is known
     as _Frege_ in the literature.  It is also proved as Theorem *2.77 of
     [WhiteheadRussell] p. 108.  The other direction of this axiom also
     turns out to be true, as demonstrated by ~ pm5.41 . $)
  ax-2 $a |- ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ps ) -> ( ph -> ch ) ) ) $.

  $( Axiom _Transp_.  Axiom A3 of [Margaris] p. 49.  One of the 3 axioms of
     propositional calculus.  It swaps or "transposes" the order of the
     consequents when negation is removed.  An informal example is that the
     statement "if there are no clouds in the sky, it is not raining" implies
     the statement "if it is raining, there are clouds in the sky."  This
     axiom is called _Transp_ or "the principle of transposition" in
     _Principia Mathematica_ (Theorem *2.17 of [WhiteheadRussell] p. 103).
     We will also use the term "contraposition" for this principle, although
     the reader is advised that in the field of philosophical logic,
     "contraposition" has a different technical meaning. $)
  ax-3 $a |- ( ( -. ph -> -. ps ) -> ( ps -> ph ) ) $.

  $(
     Postulate the modus ponens rule of inference.
  $)

  ${
    $( Minor premise for modus ponens. $)
    min $e |- ph $.
    $( Major premise for modus ponens. $)
    maj $e |- ( ph -> ps ) $.
    $( Rule of Modus Ponens.  The postulated inference rule of propositional
       calculus.  See e.g. Rule 1 of [Hamilton] p. 73.  The rule says, "if
       ` ph ` is true, and ` ph ` implies ` ps ` , then ` ps ` must also be
       true."  This rule is sometimes called "detachment," since it detaches
       the minor premise from the major premise. $)
    ax-mp $a |- ps $.
  $}

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical implication
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

$( The results in this section make use of the first 2 axioms only.  In
   an implication, the wff before the arrow is called the "antecedent"
   and the wff after the arrow is called the "consequent." $)

$( We will use the following descriptive terms very loosely:  A "theorem"
   usually has no $e hypotheses.  An "inference" has one or more $e hypotheses.
   A "deduction" is an inference in which the hypotheses and the result
   share the same antecedent. $)

  ${
    $( Premise for ~ a1i . $)
    a1i.1 $e |- ph $.
    $( Inference derived from axiom ~ ax-1 .  See ~ a1d for an explanation of
       our informal use of the terms "inference" and "deduction." $)
    a1i $p |- ( ps -> ph ) $=
      wph wps wph wi a1i.1 wph wps ax-1 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ a2i . $)
    a2i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference derived from axiom ~ ax-2 . $)
    a2i $p |- ( ( ph -> ps ) -> ( ph -> ch ) ) $=
      wph wps wch wi wi wph wps wi wph wch wi wi a2i.1 wph wps wch ax-2 ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( First of 2 premises for ~ syl . $)
    syl.1 $e |- ( ph -> ps ) $.
    $( Second of 2 premises for ~ syl . $)
    syl.2 $e |- ( ps -> ch ) $.
    $( An inference version of the transitive laws for implication ~ imim2 and
       ~ imim1 , which Russell and Whitehead call "the principle of the
       syllogism...because...the syllogism in Barbara is derived from them"
       (quote after Theorem *2.06 of [WhiteheadRussell] p. 101).  Some authors
       call this law a "hypothetical syllogism."

       (A bit of trivia:  this is the most commonly referenced assertion in our
       database.  In second place is ~ ax-mp , followed by ~ visset , ~ bitr ,
       ~ imp , and ~ ex .  The Metamath program command 'show usage' shows the
       number of references.) $)
    syl $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi syl.1 wph wps wch wps wch wi wph syl.2 a1i a2i
      ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    $( Premise for ~ com12 .  See ~ pm2.04 for the theorem form. $)
    com12.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference that swaps (commutes) antecedents in an implication. $)
    com12 $p |- ( ps -> ( ph -> ch ) ) $=
      wps wph wps wi wph wch wi wps wph ax-1 wph wps wch com12.1 a2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    a1d.1 $e |- ( ph -> ps ) $.
    $( Deduction introducing an embedded antecedent.  (The proof was revised by
       Stefan Allan, 20-Mar-06.)

       _Naming convention_:  We often call a theorem a "deduction" and suffix
       its label with "d" whenever the hypotheses and conclusion are each
       prefixed with the same antecedent.  This allows us to use the theorem in
       places where (in traditional textbook formalizations) the standard
       Deduction Theorem would be used; here ` ph ` would be replaced with a
       conjunction ( ~ df-an ) of the hypotheses of the would-be deduction.  By
       contrast, we tend to call the simpler version with no common antecedent
       an "inference" and suffix its label with "i"; compare theorem ~ a1i .
       Finally, a "theorem" would be the form with no hypotheses; in this case
       the "theorem" form would be the original axiom ~ ax-1 .  In
       propositional calculus we usually prove the theorem form first without a
       suffix on its label (e.g.  ~ pm2.43 vs.  ~ pm2.43i vs.  ~ pm2.43d ), but
       (much) later we often suffix the theorem form's label with "t" as in
       ~ negnegt vs. ~ negneg , especially when our "weak deduction theorem"
       ~ dedth is used to prove the theorem form from its inference form.  When
       an inference is converted to a theorem by eliminating an "is a set"
       hypothesis, we sometimes suffix the theorem form with "g" (for somewhat
       overstated "generalized") as in ~ uniex vs.  ~ uniexg . $)
    a1d $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wch wps wi a1d.1 wps wch ax-1 syl $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    a2d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Deduction distributing an embedded antecedent. $)
    a2d $p |- ( ph -> ( ( ps -> ch ) -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wps wch wi wps wth wi wi a2d.1 wps wch wth ax-2 syl
      $.
      $( [23-Jun-1994] $)
  $}

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.05 of
     [WhiteheadRussell] p. 100. $)
  imim2 $p |- ( ( ph -> ps ) -> ( ( ch -> ph ) -> ( ch -> ps ) ) ) $=
    wph wps wi wch wph wps wph wps wi wch ax-1 a2d $.
    $( [5-Aug-1993] $)

  $( A closed form of syllogism (see ~ syl ).  Theorem *2.06 of
     [WhiteheadRussell] p. 100. $)
  imim1 $p |- ( ( ph -> ps ) -> ( ( ps -> ch ) -> ( ph -> ch ) ) ) $=
    wps wch wi wph wps wi wph wch wi wps wch wph imim2 com12 $.
    $( [5-Aug-1993] $)

  ${
    imim1i.1 $e |- ( ph -> ps ) $.
    $( Inference adding common consequents in an implication, thereby
       interchanging the original antecedent and consequent. $)
    imim1i $p |- ( ( ps -> ch ) -> ( ph -> ch ) ) $=
      wph wps wi wps wch wi wph wch wi wi imim1i.1 wph wps wch imim1 ax-mp $.
      $( [5-Aug-1993] $)

    $( Inference adding common antecedents in an implication. $)
    imim2i $p |- ( ( ch -> ph ) -> ( ch -> ps ) ) $=
      wch wph wps wph wps wi wch imim1i.1 a1i a2i $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim12i.1 $e |- ( ph -> ps ) $.
    imim12i.2 $e |- ( ch -> th ) $.
    $( Inference joining two implications. $)
    imim12i $p |- ( ( ps -> ch ) -> ( ph -> th ) ) $=
      wps wch wi wps wth wi wph wth wi wch wth wps imim12i.2 imim2i wph wps wth
      imim12i.1 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    imim3i.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Inference adding three nested antecedents. $)
    imim3i $p |- ( ( th -> ph ) -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wth wph wi wth wps wch wph wps wch wi wth imim3i.1 imim2i a2d $.
      $( [19-Dec-2006] $) $( [19-Dec-2006] $)
  $}

  ${
    3syl.1 $e |- ( ph -> ps ) $.
    3syl.2 $e |- ( ps -> ch ) $.
    3syl.3 $e |- ( ch -> th ) $.
    $( Inference chaining two syllogisms. $)
    3syl $p |- ( ph -> th ) $=
      wph wch wth wph wps wch 3syl.1 3syl.2 syl 3syl.3 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl5.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5.2 $e |- ( th -> ps ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the second antecedent of the first premise. $)
    syl5 $p |- ( ph -> ( th -> ch ) ) $=
      wph wps wch wi wth wch wi syl5.1 wth wps wch syl5.2 imim1i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl6.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6.2 $e |- ( ch -> th ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl6 $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syl6.1 wch wth wps syl6.2 imim2i syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl7.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl7.2 $e |- ( ta -> ch ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the third antecedent of the first premise. $)
    syl7 $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wch wth wi wta wth wi syl7.1 wta wch wth syl7.2 imim1i syl6 $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl8.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl8.2 $e |- ( th -> ta ) $.
    $( A syllogism rule of inference.  The second premise is used to replace
       the consequent of the first premise. $)
    syl8 $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syl8.1 wth wta wch syl8.2 imim2i syl6 $.
      $( [1-Aug-1994] $)
  $}

  ${
    imim2d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested antecedents. $)
    imim2d $p |- ( ph -> ( ( th -> ps ) -> ( th -> ch ) ) ) $=
      wph wth wps wch wph wps wch wi wth imim2d.1 a1d a2d $.
      $( [5-Aug-1993] $)
  $}

  ${
    mpd.1 $e |- ( ph -> ps ) $.
    mpd.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A modus ponens deduction. $)
    mpd $p |- ( ph -> ch ) $=
      wph wps wi wph wch wi mpd.1 wph wps wch mpd.2 a2i ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    syld.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syld.2 $e |- ( ph -> ( ch -> th ) ) $.
    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       19-Feb-2008.  See ~ syldOLD for previous version.) $)
    syld $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi syld.1 wph wch wth wps syld.2 imim2d mpd $.
      $( [19-Feb-2008] $) $( [5-Aug-1993] $)

    $( Syllogism deduction.  (The proof was shortened by Mel L. O'Cat,
       7-Aug-2004.) $)
    syldOLD $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wi wph wps wth wi wi syld.1 wph wps wch wi wps wth wi wph
      wch wth wps syld.2 imim2d a2i ax-mp $.
      $( [7-Aug-2004] $) $( [5-Aug-1993] $)
  $}

  ${
    imim1d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction adding nested consequents. $)
    imim1d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> th ) ) ) $=
      wph wps wch wi wch wth wi wps wth wi wi imim1d.1 wps wch wth imim1 syl $.
      $( [3-Apr-1994] $)
  $}

  ${
    imim12d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    imim12d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( Deduction combining antecedents and consequents. $)
    imim12d $p |- ( ph -> ( ( ch -> th ) -> ( ps -> ta ) ) ) $=
      wph wch wth wi wps wth wi wps wta wi wph wps wch wth imim12d.1 imim1d wph
      wth wta wps imim12d.2 imim2d syld $.
      $( [7-Aug-1994] $)
  $}

  $( Swap antecedents.  Theorem *2.04 of [WhiteheadRussell] p. 100. $)
  pm2.04 $p |- ( ( ph -> ( ps -> ch ) ) -> ( ps -> ( ph -> ch ) ) ) $=
    wph wps wch wi wi wph wps wi wph wch wi wps wph wps wch ax-2 wps wph ax-1
    syl5 $.
    $( [5-Aug-1993] $)

  $( Theorem *2.83 of [WhiteheadRussell] p. 108. $)
  pm2.83 $p |-  ( ( ph -> ( ps -> ch ) ) -> ( ( ph -> ( ch -> th ) ) ->
                ( ph -> ( ps -> th ) ) ) ) $=
    wps wch wi wch wth wi wps wth wi wph wps wch wth imim1 imim3i $.
    $( [13-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    com3.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( Commutation of antecedents.  Swap 2nd and 3rd. $)
    com23 $p |- ( ph -> ( ch -> ( ps -> th ) ) ) $=
      wph wps wch wth wi wi wch wps wth wi wi com3.1 wps wch wth pm2.04 syl $.
      $( [5-Aug-1993] $)

    $( Commutation of antecedents.  Swap 1st and 3rd. $)
    com13 $p |- ( ch -> ( ps -> ( ph -> th ) ) ) $=
      wps wch wph wth wi wps wph wch wth wph wps wch wth wi com3.1 com12 com23
      com12 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left. $)
    com3l $p |- ( ps -> ( ch -> ( ph -> th ) ) ) $=
      wph wch wps wth wph wps wch wth com3.1 com23 com13 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com3r $p |- ( ch -> ( ph -> ( ps -> th ) ) ) $=
      wps wch wph wth wph wps wch wth com3.1 com3l com3l $.
      $( [25-Apr-1994] $)
  $}

  ${
    com4.1 $e |- ( ph -> ( ps -> ( ch -> ( th -> ta ) ) ) ) $.
    $( Commutation of antecedents.  Swap 3rd and 4th. $)
    com34 $p |- ( ph -> ( ps -> ( th -> ( ch -> ta ) ) ) ) $=
      wph wps wch wth wta wi wi wth wch wta wi wi com4.1 wch wth wta pm2.04
      syl6 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 2nd and 4th. $)
    com24 $p |- ( ph -> ( th -> ( ch -> ( ps -> ta ) ) ) ) $=
      wph wth wps wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com23 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Swap 1st and 4th. $)
    com14 $p |- ( th -> ( ps -> ( ch -> ( ph -> ta ) ) ) ) $=
      wth wps wph wch wta wph wps wth wch wta wi wph wps wch wth wta com4.1
      com34 com13 com34 $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate left.  (The proof was shortened by
       Mel L. O'Cat, 15-Aug-2004.) $)
    com4l $p |- ( ps -> ( ch -> ( th -> ( ph -> ta ) ) ) ) $=
      wth wps wch wph wta wi wph wps wch wth wta com4.1 com14 com3l $.
      $( [15-Aug-2004] $) $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate twice. $)
    com4t $p |- ( ch -> ( th -> ( ph -> ( ps -> ta ) ) ) ) $=
      wps wch wth wph wta wph wps wch wth wta com4.1 com4l com4l $.
      $( [25-Apr-1994] $)

    $( Commutation of antecedents.  Rotate right. $)
    com4r $p |- ( th -> ( ph -> ( ps -> ( ch -> ta ) ) ) ) $=
      wch wth wph wps wta wph wps wch wth wta com4.1 com4t com4l $.
      $( [25-Apr-1994] $)
  $}

  ${
    a1dd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Deduction introducing a nested embedded antecedent.  (The proof was
       shortened by Mel L. O'Cat, 15-Jan-2008.) $)
    a1dd $p |- ( ph -> ( ps -> ( th -> ch ) ) ) $=
      wph wps wch wth wch wi a1dd.1 wch wth ax-1 syl6 $.
      $( [15-Jan-2008] $) $( [17-Dec-2004] $)
  $}

  ${
    mp2.1 $e |- ph $.
    mp2.2 $e |- ps $.
    mp2.3 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A double modus ponens inference. $)
    mp2 $p |- ch $=
      wps wch mp2.2 wph wps wch wi mp2.1 mp2.3 ax-mp ax-mp $.
      $( [5-Apr-1994] $)
  $}

  ${
    mpi.1 $e |- ps $.
    mpi.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A nested modus ponens inference.  (The proof was shortened by Stefan
       Allan, 20-Mar-06. $)
    mpi $p |- ( ph -> ch ) $=
      wph wps wch wps wph mpi.1 a1i mpi.2 mpd $.
      $( [20-Mar-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    mpii.1 $e |- ch $.
    mpii.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A doubly nested modus ponens inference. $)
    mpii $p |- ( ph -> ( ps -> th ) ) $=
      wph wch wps wth wi mpii.1 wph wps wch wth mpii.2 com23 mpi $.
      $( [31-Dec-1993] $)
  $}

  ${
    mpdd.1 $e |- ( ph -> ( ps -> ch ) ) $.
    mpdd.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpdd $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi mpdd.1 wph wps wch wth mpdd.2 a2d mpd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    mpid.1 $e |- ( ph -> ch ) $.
    mpid.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction. $)
    mpid $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wph wch wps mpid.1 a1d mpid.2 mpdd $.
      $( [16-Dec-2004] $) $( [14-Dec-2004] $)
  $}

  ${
    mpdi.1 $e |- ( ps -> ch ) $.
    mpdi.2 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    $( A nested modus ponens deduction.  (The proof was shortened by Mel L.
       O'Cat, 15-Jan-2008.) $)
    mpdi $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wth wps wch wi wph mpdi.1 a1i mpdi.2 mpdd $.
      $( [15-Jan-2008] $) $( [16-Apr-2005] $)
  $}

  ${
    mpcom.1 $e |- ( ps -> ph ) $.
    mpcom.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus ponens inference with commutation of antecedents. $)
    mpcom $p |- ( ps -> ch ) $=
      wps wph wch mpcom.1 wph wps wch mpcom.2 com12 mpd $.
      $( [17-Mar-1996] $)
  $}

  ${
    syldd.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syldd.2 $e |- ( ph -> ( ps -> ( th -> ta ) ) ) $.
    $( Nested syllogism deduction. $)
    syldd $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wi wch wta wi syldd.1 wph wps wth wta wi wch wth wi wch
      wta wi wi syldd.2 wth wta wch imim2 syl6 mpdd $.
      $( [13-Dec-2004] $) $( [12-Dec-2004] $)
  $}

  ${
    sylcom.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylcom.2 $e |- ( ps -> ( ch -> th ) ) $.
    $( Syllogism inference with commutation of antecedents.  (The proof was
       shortened by Mel O'Cat, 2-Feb-06 and shortened further by Stefan Allan,
       23-Feb-06.) $)
    sylcom $p |- ( ph -> ( ps -> th ) ) $=
      wph wps wch wi wps wth wi sylcom.1 wps wch wth sylcom.2 a2i syl $.
      $( [24-Feb-2006] $) $( [29-Aug-2004] $)
  $}

  ${
    syl5com.2 $e |- ( ph -> ( ps -> ch ) ) $.
    syl5com.1 $e |- ( th -> ps ) $.
    $( Syllogism inference with commuted antecedents. $)
    syl5com $p |- ( th -> ( ph -> ch ) ) $=
      wth wph wps wch wth wps wph syl5com.1 a1d syl5com.2 sylcom $.
      $( [25-May-2005] $) $( [24-May-2005] $)
  $}

  ${
    syl6com.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl6com.2 $e |- ( ch -> th ) $.
    $( Syllogism inference with commuted antecedents. $)
    syl6com $p |- ( ps -> ( ph -> th ) ) $=
      wph wps wth wph wps wch wth syl6com.1 syl6com.2 syl6 com12 $.
      $( [26-May-2005] $) $( [25-May-2005] $)
  $}

  ${
    syli.1 $e |- ( ps -> ( ph -> ch ) ) $.
    syli.2 $e |- ( ch -> ( ph -> th ) ) $.
    $( Syllogism inference with common nested antecedent. $)
    syli $p |- ( ps -> ( ph -> th ) ) $=
      wps wph wch wth syli.1 wch wph wth syli.2 com12 sylcom $.
      $( [5-Nov-2004] $) $( [4-Nov-2004] $)
  $}

  ${
    syl5d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl5d.2 $e |- ( ph -> ( ta -> ch ) ) $.
    $( A nested syllogism deduction.  (The proof was shortened by Josh
       Purinton, 29-Dec-00 and shortened further by Mel O'Cat, 2-Feb-06.) $)
    syl5d $p |- ( ph -> ( ps -> ( ta -> th ) ) ) $=
      wph wps wta wch wth wph wta wch wi wps syl5d.2 a1d syl5d.1 syldd $.
      $( [3-Feb-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    syl6d.1 $e |- ( ph -> ( ps -> ( ch -> th ) ) ) $.
    syl6d.2 $e |- ( ph -> ( th -> ta ) ) $.
    $( A nested syllogism deduction.  (The proof was shortened by Josh
       Purinton, 29-Dec-00 and shortened further by Mel O'Cat, 2-Feb-06.) $)
    syl6d $p |- ( ph -> ( ps -> ( ch -> ta ) ) ) $=
      wph wps wch wth wta syl6d.1 wph wth wta wi wps syl6d.2 a1d syldd $.
      $( [3-Feb-2006] $) $( [5-Aug-1993] $)
  $}

  ${
    syl9.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl9.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( A nested syllogism inference with different antecedents.  (The proof
       was shortened by Josh Purinton, 29-Dec-00.) $)
    syl9 $p |- ( ph -> ( th -> ( ps -> ta ) ) ) $=
      wph wth wch wta wps wth wch wta wi wi wph syl9.2 a1i syl9.1 syl5d $.
      $( [5-Aug-1993] $)
  $}

  ${
    syl9r.1 $e |- ( ph -> ( ps -> ch ) ) $.
    syl9r.2 $e |- ( th -> ( ch -> ta ) ) $.
    $( A nested syllogism inference with different antecedents. $)
    syl9r $p |- ( th -> ( ph -> ( ps -> ta ) ) ) $=
      wph wth wps wta wi wph wps wch wth wta syl9r.1 syl9r.2 syl9 com12 $.
      $( [5-Aug-1993] $)
  $}

  $( Principle of identity.  Theorem *2.08 of [WhiteheadRussell] p. 101.
     For another version of the proof directly from axioms, see ~ id1 .
     (The proof was shortened by Stefan Allan, 20-Mar-06.) $)
  id $p |- ( ph -> ph ) $=
    wph wph wph wi wph wph wph ax-1 wph wph wph wi ax-1 mpd $.
    $( [20-Mar-2006] $) $( [20-Mar-2006] $)

  $( Principle of identity.  Theorem *2.08 of [WhiteheadRussell] p. 101.  This
     version is proved directly from the axioms for demonstration purposes.
     This proof is a very popular example in the literature and is identical,
     step for step, to the proofs of Theorem 1 of [Margaris] p. 51,
     Example 2.7(a) of [Hamilton] p. 31, Lemma 10.3 of [BellMachover] p. 36,
     and Lemma 1.8 of [Mendelson] p. 36.  It is also
     "Our first proof" in Hirst and Hirst's _A Primer for Logic and Proof_
     p. 16 (PDF p. 22) at
     ~ http://www.mathsci.appstate.edu/~~jlh/primer/hirst.pdf .
     For a shorter version of the proof that takes advantage of previously
     proved theorems, see ~ id . $)
  id1 $p |- ( ph -> ph ) $=
    wph wph wph wi wi wph wph wi wph wph ax-1 wph wph wph wi wph wi wi wph wph
    wph wi wi wph wph wi wi wph wph wph wi ax-1 wph wph wph wi wph ax-2 ax-mp
    ax-mp $.
    $( [5-Aug-1993] $)

  $( Principle of identity with antecedent. $)
  idd $p |- ( ph -> ( ps -> ps ) ) $=
    wps wps wi wph wps id a1i $.
    $( [26-Nov-1995] $)

  $( This theorem, called "Assertion," can be thought of as closed form of
     modus ponens.  Theorem *2.27 of [WhiteheadRussell] p. 104. $)
  pm2.27 $p |- ( ph -> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wi wph wps wph wps wi id com12 $.
    $( [5-Aug-1993] $)

  $( Absorption of redundant antecedent.  Also called the "Contraction" or
     "Hilbert" axiom.  Theorem *2.43 of [WhiteheadRussell] p. 106.  (The proof
     was shortened by Mel L. O'Cat, 15-Aug-2004.) $)
  pm2.43 $p |- ( ( ph -> ( ph -> ps ) ) -> ( ph -> ps ) ) $=
    wph wph wps wi wps wph wps pm2.27 a2i $.
    $( [15-Aug-2004] $) $( [5-Aug-1993] $)

  ${
    pm2.43i.1 $e |- ( ph -> ( ph -> ps ) ) $.
    $( Inference absorbing redundant antecedent. $)
    pm2.43i $p |- ( ph -> ps ) $=
      wph wph wps wi wi wph wps wi pm2.43i.1 wph wps pm2.43 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.43d.1 $e |- ( ph -> ( ps -> ( ps -> ch ) ) ) $.
    $( Deduction absorbing redundant antecedent.  (The proof was shortened by
       Mel O'Cat, 3-Feb-06.) $)
    pm2.43d $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wps wch wph wps idd pm2.43d.1 mpdd $.
      $( [4-Feb-2006] $) $( [18-Aug-1993] $)
  $}

  ${
    pm2.43a.1 $e |- ( ps -> ( ph -> ( ps -> ch ) ) ) $.
    $( Inference absorbing redundant antecedent.  (The proof was shortened by
       Mel O'Cat, 3-Feb-06.) $)
    pm2.43a $p |- ( ps -> ( ph -> ch ) ) $=
      wps wph wps wch wps wph ax-1 pm2.43a.1 mpdd $.
      $( [4-Feb-2006] $) $( [7-Nov-1995] $)

    $( Inference absorbing redundant antecedent. $)
    pm2.43b $p |- ( ph -> ( ps -> ch ) ) $=
      wps wph wch wph wps wch pm2.43a.1 pm2.43a com12 $.
      $( [31-Oct-1995] $)
  $}

  ${
    sylc.1 $e |- ( ph -> ( ps -> ch ) ) $.
    sylc.2 $e |- ( th -> ph ) $.
    sylc.3 $e |- ( th -> ps ) $.
    $( A syllogism inference combined with contraction. $)
    sylc $p |- ( th -> ch ) $=
      wth wps wch sylc.3 wth wph wps wch wi sylc.2 sylc.1 syl mpd $.
      $( [4-May-1994] $)
  $}

  $( Converse of axiom ~ ax-2 .  Theorem *2.86 of [WhiteheadRussell] p. 108. $)
  pm2.86 $p |- ( ( ( ph -> ps ) -> ( ph -> ch ) ) ->
               ( ph -> ( ps -> ch ) ) ) $=
    wph wps wi wph wch wi wi wps wph wch wps wph wps wi wph wch wi wps wph ax-1
    imim1i com23 $.
    $( [25-Apr-1994] $)

  ${
    pm2.86i.1 $e |- ( ( ph -> ps ) -> ( ph -> ch ) ) $.
    $( Inference based on ~ pm2.86 . $)
    pm2.86i $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wi wph wch wi wi wph wps wch wi wi pm2.86i.1 wph wps wch pm2.86
      ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.86d.1 $e |- ( ph -> ( ( ps -> ch ) -> ( ps -> th ) ) ) $.
    $( Deduction based on ~ pm2.86 . $)
    pm2.86d $p |- ( ph -> ( ps -> ( ch -> th ) ) ) $=
      wph wps wch wi wps wth wi wi wps wch wth wi wi pm2.86d.1 wps wch wth
      pm2.86 syl $.
      $( [29-Jun-1995] $)
  $}

  $( The Linearity Axiom of the infinite-valued sentential logic (L-infinity)
     of Lukasiewicz.  (Contributed by Mel L. O'Cat, 12-Aug-2004.) $)
  loolin $p |- ( ( ( ph -> ps ) -> ( ps -> ph ) ) -> ( ps -> ph ) ) $=
    wph wps wi wps wph wi wi wps wph wps wph wps wi wps wph wi wps wph ax-1
    imim1i pm2.43d $.
    $( [14-Aug-2004] $) $( [12-Aug-2004] $)

  $( An alternate for the Linearity Axiom of the infinite-valued sentential
     logic (L-infinity) of Lukasiewicz, due to Barbara Wozniakowska, _Reports
     on Mathematical Logic_ 10, 129-137 (1978).  (Contributed by Mel L. O'Cat,
     8-Aug-2004.) $)
  loowoz $p |- ( ( ( ph -> ps ) -> ( ph -> ch ) ) ->
                 ( ( ps -> ph ) -> ( ps -> ch ) ) ) $=
    wph wps wi wph wch wi wi wps wph wch wps wph wps wi wph wch wi wps wph ax-1
    imim1i a2d $.
    $( [9-Aug-2004] $) $( [8-Aug-2004] $)

$(
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        Logical negation
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
$)

$( This section makes our first use of the third axiom of propositonal
   calculus. $)

  ${
    a3i.1 $e |- ( -. ph -> -. ps ) $.
    $( Inference rule derived from axiom ~ ax-3 . $)
    a3i $p |- ( ps -> ph ) $=
      wph wn wps wn wi wps wph wi a3i.1 wph wps ax-3 ax-mp $.
      $( [5-Aug-1993] $)
  $}

  ${
    a3d.1 $e |- ( ph -> ( -. ps -> -. ch ) ) $.
    $( Deduction derived from axiom ~ ax-3 . $)
    a3d $p |- ( ph -> ( ch -> ps ) ) $=
      wph wps wn wch wn wi wch wps wi a3d.1 wps wch ax-3 syl $.
      $( [26-Mar-1995] $)
  $}

  $( From a wff and its negation, anything is true.  Theorem *2.21 of
     [WhiteheadRussell] p. 104.  Also called the Duns Scotus law. $)
  pm2.21 $p |- ( -. ph -> ( ph -> ps ) ) $=
    wph wn wps wph wph wn wps wn ax-1 a3d $.
    $( [5-Aug-1993] $)

  ${
    pm2.21i.1 $e |- -. ph $.
    $( A contradiction implies anything.  Inference from ~ pm2.21 . $)
    pm2.21i $p |- ( ph -> ps ) $=
      wps wph wph wn wps wn pm2.21i.1 a1i a3i $.
      $( [16-Sep-1993] $)
  $}

  ${
    pm2.21d.1 $e |- ( ph -> -. ps ) $.
    $( A contradiction implies anything.  Deduction from ~ pm2.21 . $)
    pm2.21d $p |- ( ph -> ( ps -> ch ) ) $=
      wph wch wps wph wps wn wch wn pm2.21d.1 a1d a3d $.
      $( [10-Feb-1996] $)
  $}

  $( Theorem *2.24 of [WhiteheadRussell] p. 104. $)
  pm2.24 $p |-  ( ph -> ( -. ph -> ps ) ) $=
    wph wn wph wps wph wps pm2.21 com12 $.
    $( [6-Jan-2005] $) $( [3-Jan-2005] $)

  ${
    pm2.24ii.1 $e |- ph $.
    pm2.24ii.2 $e |- -. ph $.
    $( A contradiction implies anything.  Inference from ~ pm2.24 . $)
    pm2.24ii $p |- ps $=
      wph wps pm2.24ii.1 wph wps pm2.24ii.2 pm2.21i ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Proof by contradiction.  Theorem *2.18 of [WhiteheadRussell] p. 103.
     Also called the Law of Clavius. $)
  pm2.18 $p |- ( ( -. ph -> ph ) -> ph ) $=
    wph wn wph wi wph wph wn wph wi wph wph wn wph wi wph wn wph wph wn wph wi
    wn wph wph wn wph wi wn pm2.21 a2i a3d pm2.43i $.
    $( [5-Aug-1993] $)

  $( Peirce's axiom.  This odd-looking theorem is the "difference" between
     an intuitionistic system of propositional calculus and a classical system
     and is not accepted by intuitionists.  When Peirce's axiom is added to an
     intuitionistic system, the system becomes equivalent to our classical
     system ~ ax-1 through ~ ax-3 .  A curious fact about this
     theorem is that it requires ~ ax-3 for its proof even though the
     result has no negation connectives in it. $)
  peirce $p |- ( ( ( ph -> ps ) -> ph ) -> ph ) $=
    wph wps wi wph wi wph wn wph wi wph wph wn wph wps wi wph wph wps pm2.21
    imim1i wph pm2.18 syl $.
    $( [5-Aug-1993] $)

  $( The Inversion Axiom of the infinite-valued sentential logic (L-infinity)
     of Lukasiewicz.  Using ~ dfor2 , we can see that this essentially
     expresses "disjunction commutes."  Theorem *2.69 of [WhiteheadRussell]
     p. 108. $)
  looinv $p |- ( ( ( ph -> ps ) -> ps ) -> ( ( ps -> ph ) -> ph ) ) $=
    wph wps wi wps wi wps wph wi wph wps wi wph wi wph wph wps wi wps wph imim1
    wph wps peirce syl6 $.
    $( [20-Aug-2004] $) $( [12-Aug-2004] $)

  $( Converse of double negation.  Theorem *2.14 of [WhiteheadRussell] p. 102.
     (The proof was shortened by David Harvey, 5-Sep-99.  An even shorter
     proof found by Josh Purinton, 29-Dec-00.) $)
  nega $p |- ( -. -. ph -> ph ) $=
    wph wn wn wph wn wph wi wph wph wn wph pm2.21 wph pm2.18 syl $.
    $( [5-Aug-1993] $)

  ${
    negai.1 $e |- -. -. ph $.
    $( Inference from double negation. $)
    negai $p |- ph $=
      wph wn wn wph negai.1 wph nega ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Converse of double negation.  Theorem *2.12 of [WhiteheadRussell]
     p. 101. $)
  negb $p |- ( ph -> -. -. ph ) $=
    wph wn wn wph wph wn nega a3i $.
    $( [5-Aug-1993] $)

  ${
    negbi.1 $e |- ph $.
    $( Infer double negation. $)
    negbi $p |- -. -. ph $=
      wph wph wn wn negbi.1 wph negb ax-mp $.
      $( [27-Feb-2008] $) $( [27-Feb-2008] $)
  $}

  $( Reductio ad absurdum.  Theorem *2.01 of [WhiteheadRussell] p. 100. $)
  pm2.01 $p |- ( ( ph -> -. ph ) -> -. ph ) $=
    wph wph wn wi wph wn wn wph wn wi wph wn wph wn wn wph wph wn wph nega
    imim1i wph wn pm2.18 syl $.
    $( [18-Aug-1993] $)

  ${
    pm2.01d.1 $e |- ( ph -> ( ps -> -. ps ) ) $.
    $( Deduction based on reductio ad absurdum. $)
    pm2.01d $p |- ( ph -> -. ps ) $=
      wph wps wps wn wi wps wn pm2.01d.1 wps pm2.01 syl $.
      $( [18-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.03 of [WhiteheadRussell] p. 100. $)
  con2 $p |- ( ( ph -> -. ps ) -> ( ps -> -. ph ) ) $=
    wph wps wn wi wph wn wps wph wn wn wph wps wn wph nega imim1i a3d $.
    $( [5-Aug-1993] $)

  ${
    con2d.1 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( A contraposition deduction. $)
    con2d $p |- ( ph -> ( ch -> -. ps ) ) $=
      wph wps wch wn wi wch wps wn wi con2d.1 wps wch con2 syl $.
      $( [19-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.15 of [WhiteheadRussell] p. 102. $)
  con1 $p |- ( ( -. ph -> ps ) -> ( -. ps -> ph ) ) $=
    wph wn wps wi wph wps wn wps wps wn wn wph wn wps negb imim2i a3d $.
    $( [5-Aug-1993] $)

  ${
    con1d.1 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( A contraposition deduction. $)
    con1d $p |- ( ph -> ( -. ch -> ps ) ) $=
      wph wps wn wch wi wch wn wps wi con1d.1 wps wch con1 syl $.
      $( [5-Aug-1993] $)
  $}

  $( Contraposition.  Theorem *2.16 of [WhiteheadRussell] p. 103. $)
  con3 $p |- ( ( ph -> ps ) -> ( -. ps -> -. ph ) ) $=
    wph wps wi wph wps wn wps wps wn wn wph wps negb imim2i con2d $.
    $( [5-Aug-1993] $)

  ${
    con3d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( A contraposition deduction. $)
    con3d $p |- ( ph -> ( -. ch -> -. ps ) ) $=
      wph wps wch wi wch wn wps wn wi con3d.1 wps wch con3 syl $.
      $( [5-Aug-1993] $)
  $}

  ${
    con1.a $e |- ( -. ph -> ps ) $.
    $( A contraposition inference. $)
    con1i $p |- ( -. ps -> ph ) $=
      wph wps wn wph wn wps wps wn wn con1.a wps negb syl a3i $.
      $( [5-Aug-1993] $)
  $}

  ${
    con2.a $e |- ( ph -> -. ps ) $.
    $( A contraposition inference. $)
    con2i $p |- ( ps -> -. ph ) $=
      wph wn wps wph wn wn wph wps wn wph nega con2.a syl a3i $.
      $( [5-Aug-1993] $)
  $}

  ${
    con3.a $e |- ( ph -> ps ) $.
    $( A contraposition inference. $)
    con3i $p |- ( -. ps -> -. ph ) $=
      wph wn wps wph wn wn wph wps wph nega con3.a syl con1i $.
      $( [5-Aug-1993] $)
  $}

  $( This is NOT theorem *2.37 of [WhiteheadRussell] p. 105. $)
  pm2.37OLD $p |-  ( ( ps -> ch ) ->
          ( ( -. ps -> ph ) -> ( -. ph -> ch ) ) ) $=
    wps wn wph wi wps wch wi wph wn wch wi wps wn wph wi wph wn wps wch wps wph
    con1 imim1d com12 $.
    $( [23-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.5 of [WhiteheadRussell] p. 107. $)
  pm2.5 $p |-  ( -. ( ph -> ps ) -> ( -. ph -> ps ) ) $=
    wph wps wi wn wph wn wps wph wn wph wps wi wph wps pm2.21 con3i pm2.21d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.51 of [WhiteheadRussell] p. 107. $)
  pm2.51 $p |-  ( -. ( ph -> ps ) -> ( ph -> -. ps ) ) $=
    wph wps wi wn wps wn wph wps wph wps wi wps wph ax-1 con3i a1d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.52 of [WhiteheadRussell] p. 107. $)
  pm2.52 $p |-  ( -. ( ph -> ps ) -> ( -. ph -> -. ps ) ) $=
    wph wps wi wn wps wn wph wn wps wph wps wi wps wph ax-1 con3i a1d $.
    $( [27-Jan-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.521 of [WhiteheadRussell] p. 107. $)
  pm2.521 $p |-  ( -. ( ph -> ps ) -> ( ps -> ph ) ) $=
    wph wps wi wn wph wps wph wps pm2.52 a3d $.
    $( [6-Feb-2005] $) $( [3-Jan-2005] $)

  ${
    pm2.24i.1 $e |- ph $.
    $( Inference version of ~ pm2.24 . $)
    pm2.24i $p |- ( -. ph -> ps ) $=
      wps wph wph wps wn pm2.24i.1 a1i con1i $.
      $( [20-Aug-2001] $)
  $}

  ${
    pm2.24d.1 $e |- ( ph -> ps ) $.
    $( Deduction version of ~ pm2.21 . $)
    pm2.24d $p |- ( ph -> ( -. ps -> ch ) ) $=
      wph wch wps wph wps wch wn pm2.24d.1 a1d con1d $.
      $( [31-Jan-2006] $) $( [30-Jan-2006] $)
  $}

  ${
    mto.1 $e |- -. ps $.
    mto.2 $e |- ( ph -> ps ) $.
    $( The rule of modus tollens. $)
    mto $p |- -. ph $=
      wps wn wph wn mto.1 wph wps mto.2 con3i ax-mp $.
      $( [19-Aug-1993] $)
  $}

  ${
    mtoi.1 $e |- -. ch $.
    mtoi.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus tollens inference. $)
    mtoi $p |- ( ph -> -. ps ) $=
      wph wch wn wps wn mtoi.1 wph wps wch mtoi.2 con3d mpi $.
      $( [5-Jul-1994] $)
  $}

  ${
    mtod.1 $e |- ( ph -> -. ch ) $.
    mtod.2 $e |- ( ph -> ( ps -> ch ) ) $.
    $( Modus tollens deduction. $)
    mtod $p |- ( ph -> -. ps ) $=
      wph wch wn wps wn mtod.1 wph wps wch mtod.2 con3d mpd $.
      $( [3-Apr-1994] $)
  $}

  ${
    mt2.1 $e |- ps $.
    mt2.2 $e |- ( ph -> -. ps ) $.
    $( A rule similar to modus tollens. $)
    mt2 $p |- -. ph $=
      wps wph wn mt2.1 wph wps mt2.2 con2i ax-mp $.
      $( [19-Aug-1993] $)
  $}

  ${
    mt2i.1 $e |- ch $.
    mt2i.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Modus tollens inference. $)
    mt2i $p |- ( ph -> -. ps ) $=
      wph wch wps wn mt2i.1 wph wps wch mt2i.2 con2d mpi $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt2d.1 $e |- ( ph -> ch ) $.
    mt2d.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Modus tollens deduction. $)
    mt2d $p |- ( ph -> -. ps ) $=
      wph wch wps wn mt2d.1 wph wps wch mt2d.2 con2d mpd $.
      $( [4-Jul-1994] $)
  $}

  ${
    mt3.1 $e |- -. ps $.
    mt3.2 $e |- ( -. ph -> ps ) $.
    $( A rule similar to modus tollens. $)
    mt3 $p |- ph $=
      wps wn wph mt3.1 wph wps mt3.2 con1i ax-mp $.
      $( [18-May-1994] $)
  $}

  ${
    mt3i.1 $e |- -. ch $.
    mt3i.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Modus tollens inference. $)
    mt3i $p |- ( ph -> ps ) $=
      wph wch wn wps mt3i.1 wph wps wch mt3i.2 con1d mpi $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt3d.1 $e |- ( ph -> -. ch ) $.
    mt3d.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Modus tollens deduction. $)
    mt3d $p |- ( ph -> ps ) $=
      wph wch wn wps mt3d.1 wph wps wch mt3d.2 con1d mpd $.
      $( [26-Mar-1995] $)
  $}

  ${
    mt4d.1 $e |- ( ph -> ps ) $.
    mt4d.2 $e |- ( ph -> ( -. ch -> -. ps ) ) $.
    $( Modus tollens deduction. $)
    mt4d $p |- ( ph -> ch ) $=
      wph wps wch mt4d.1 wph wch wps mt4d.2 a3d mpd $.
      $( [18-Jun-2006] $) $( [9-Jun-2006] $)
  $}

  ${
    nsyl.1 $e |- ( ph -> -. ps ) $.
    nsyl.2 $e |- ( ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl $p |- ( ph -> -. ch ) $=
      wph wps wn wch wn nsyl.1 wch wps nsyl.2 con3i syl $.
      $( [31-Dec-1993] $)
  $}

  ${
    nsyld.1 $e |- ( ph -> ( ps -> -. ch ) ) $.
    nsyld.2 $e |- ( ph -> ( ta -> ch ) ) $.
    $( A negated syllogism deduction. $)
    nsyld $p |- ( ph -> ( ps -> -. ta ) ) $=
      wph wps wch wn wta wn nsyld.1 wph wta wch nsyld.2 con3d syld $.
      $( [10-Apr-2005] $) $( [9-Apr-2005] $)
  $}

  ${
    nsyl2.1 $e |- ( ph -> -. ps ) $.
    nsyl2.2 $e |- ( -. ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl2 $p |- ( ph -> ch ) $=
      wph wps wn wch nsyl2.1 wch wps nsyl2.2 con1i syl $.
      $( [26-Jun-1994] $)
  $}

  ${
    nsyl3.1 $e |- ( ph -> -. ps ) $.
    nsyl3.2 $e |- ( ch -> ps ) $.
    $( A negated syllogism inference. $)
    nsyl3 $p |- ( ch -> -. ph ) $=
      wch wps wph wn nsyl3.2 wph wps nsyl3.1 con2i syl $.
      $( [1-Dec-1995] $)
  $}

  ${
    nsyl4.1 $e |- ( ph -> ps ) $.
    nsyl4.2 $e |- ( -. ph -> ch ) $.
    $( A negated syllogism inference. $)
    nsyl4 $p |- ( -. ch -> ps ) $=
      wch wn wph wps wph wch nsyl4.2 con1i nsyl4.1 syl $.
      $( [15-Feb-1996] $)
  $}

  ${
    nsyli.1 $e |- ( ph -> ( ps -> ch ) ) $.
    nsyli.2 $e |- ( th -> -. ch ) $.
    $( A negated syllogism inference. $)
    nsyli $p |- ( ph -> ( th -> -. ps ) ) $=
      wph wch wn wps wn wth wph wps wch nsyli.1 con3d nsyli.2 syl5 $.
      $( [3-May-1994] $)
  $}

  $( Theorem *3.2 of [WhiteheadRussell] p. 111, expressed with primitive
     connectives.  (The proof was shortened by Josh Purinton, 29-Dec-00.) $)
  pm3.2im $p |- ( ph -> ( ps -> -. ( ph -> -. ps ) ) ) $=
    wph wph wps wn wi wps wph wps wn pm2.27 con2d $.
    $( [5-Aug-1993] $)

  $( Theorem 8 of [Margaris] p. 60.  (The proof was shortened by Josh Purinton,
     29-Dec-00.) $)
  mth8 $p |- ( ph -> ( -. ps -> -. ( ph -> ps ) ) ) $=
    wph wph wps wi wps wph wps pm2.27 con3d $.
    $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent.  (The proof was shortened by Mel L. O'Cat, 19-Feb-2008.) $)
  pm2.61 $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wn wps wi wph wps wi wps wn wps wi wps wph wn wps wi wps wn wph wps wph
    wps con1 imim1d wps pm2.18 syl6com $.
    $( [6-Mar-2008] $) $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent.  (The proof was shortened by Mel L. O'Cat, 19-Feb-2008.) $)
  pm2.61-ocatOLD $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wps wi wph wn wps wi wps wn wps wi wps wps wph wps pm2.37OLD wps pm2.18
    syl6 $.
    $( [19-Feb-2008] $) $( [5-Aug-1993] $)

  $( Theorem *2.61 of [WhiteheadRussell] p. 107.  Useful for eliminating an
     antecedent. $)
  pm2.61OLD $p |- ( ( ph -> ps ) -> ( ( -. ph -> ps ) -> ps ) ) $=
    wph wps wi wps wn wph wi wps wph wn wps wi wph wps wi wps wn wph wi wps wn
    wps wi wps wph wps wps wn imim2 wps pm2.18 syl6 wph wps con1 syl5 $.
    $( [5-Aug-1993] $)

  ${
    pm2.61i.1 $e |- ( ph -> ps ) $.
    pm2.61i.2 $e |- ( -. ph -> ps ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61i $p |- ps $=
      wph wps wi wph wn wps wi wps pm2.61i.1 pm2.61i.2 wph wps pm2.61 mp2 $.
      $( [5-Apr-1994] $)
  $}

  ${
    pm2.61d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61d.2 $e |- ( ph -> ( -. ps -> ch ) ) $.
    $( Deduction eliminating an antecedent. $)
    pm2.61d $p |- ( ph -> ch ) $=
      wps wph wch wi wph wps wch pm2.61d.1 com12 wph wps wn wch pm2.61d.2 com12
      pm2.61i $.
      $( [27-Apr-1994] $)
  $}

  ${
    pm2.61d1.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61d1.2 $e |- ( -. ps -> ch ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61d1 $p |- ( ph -> ch ) $=
      wph wps wch pm2.61d1.1 wps wn wch wi wph pm2.61d1.2 a1i pm2.61d $.
      $( [20-Jul-2005] $) $( [15-Jul-2005] $)
  $}

  ${
    pm2.61d2.1 $e |- ( ph -> ( -. ps -> ch ) ) $.
    pm2.61d2.2 $e |- ( ps -> ch ) $.
    $( Inference eliminating an antecedent. $)
    pm2.61d2 $p |- ( ph -> ch ) $=
      wph wps wch wps wch wi wph pm2.61d2.2 a1i pm2.61d2.1 pm2.61d $.
      $( [18-Aug-1993] $)
  $}

  ${
    pm2.61ii.1 $e |- ( -. ph -> ( -. ps -> ch ) ) $.
    pm2.61ii.2 $e |- ( ph -> ch ) $.
    pm2.61ii.3 $e |- ( ps -> ch ) $.
    $( Inference eliminating two antecedents.  (The proof was shortened by Josh
       Purinton,  29-Dec-00.) $)
    pm2.61ii $p |- ch $=
      wph wch pm2.61ii.2 wph wn wps wch pm2.61ii.1 pm2.61ii.3 pm2.61d2 pm2.61i
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.61nii.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.61nii.2 $e |- ( -. ph -> ch ) $.
    pm2.61nii.3 $e |- ( -. ps -> ch ) $.
    $( Inference eliminating two antecedents. $)
    pm2.61nii $p |- ch $=
      wps wch wps wph wch wph wps wch pm2.61nii.1 com12 pm2.61nii.2 pm2.61d1
      pm2.61nii.3 pm2.61i $.
      $( [5-Aug-1993] $)
  $}

  ${
    pm2.61iii.1 $e |- ( -. ph -> ( -. ps -> ( -. ch -> th ) ) ) $.
    pm2.61iii.2 $e |- ( ph -> th ) $.
    pm2.61iii.3 $e |- ( ps -> th ) $.
    pm2.61iii.4 $e |- ( ch -> th ) $.
    $( Inference eliminating three antecedents. $)
    pm2.61iii $p |- th $=
      wps wch wth wph wps wn wch wn wth wi wi wph wch wn wth wi wps wn wph wth
      wch wn pm2.61iii.2 a1d a1d pm2.61iii.1 pm2.61i pm2.61iii.3 pm2.61iii.4
      pm2.61ii $.
      $( [2-Jan-2002] $)
  $}

  $( Theorem *2.6 of [WhiteheadRussell] p. 107. $)
  pm2.6 $p |-  ( ( -. ph -> ps ) -> ( ( ph -> ps ) -> ps ) ) $=
    wph wps wi wph wn wps wi wps wph wps pm2.61 com12 $.
    $( [1-Feb-2005] $) $( [3-Jan-2005] $)

  $( Theorem *2.65 of [WhiteheadRussell] p. 107.  Useful for eliminating a
     consequent. $)
  pm2.65 $p |- ( ( ph -> ps ) -> ( ( ph -> -. ps ) -> -. ph ) ) $=
    wph wps wi wph wph wps wn wi wph wps wph wps wn wi wn wph wps pm3.2im a2i
    con2d $.
    $( [5-Aug-1993] $)

  ${
    pm2.65i.1 $e |- ( ph -> ps ) $.
    pm2.65i.2 $e |- ( ph -> -. ps ) $.
    $( Inference rule for proof by contradiction. $)
    pm2.65i $p |- -. ph $=
      wph wph wn wi wph wn wph wps wph pm2.65i.2 pm2.65i.1 nsyl wph pm2.01
      ax-mp $.
      $( [18-May-1994] $)
  $}

  ${
    pm2.65d.1 $e |- ( ph -> ( ps -> ch ) ) $.
    pm2.65d.2 $e |- ( ph -> ( ps -> -. ch ) ) $.
    $( Deduction rule for proof by contradiction. $)
    pm2.65d $p |- ( ph -> -. ps ) $=
      wps wch wi wps wch wn wi wps wn wph wps wch pm2.65 pm2.65d.1 pm2.65d.2
      sylc $.
      $( [26-Jun-1994] $)
  $}

  ${
    ja.1 $e |- ( -. ph -> ch ) $.
    ja.2 $e |- ( ps -> ch ) $.
    $( Inference joining the antecedents of two premises.  (The proof was
       shortened by Mel L. O'Cat, 19-Feb-2008.) $)
    ja $p |- ( ( ph -> ps ) -> ch ) $=
      wph wps wi wph wch wps wch wph ja.2 imim2i ja.1 pm2.61d1 $.
      $( [19-Feb-2008] $) $( [5-Aug-1993] $)

    $( Inference joining the antecedents of two premises.  (The proof was
       shortened by Mel L. O'Cat, 30-Aug-2004.) $)
    jaOLD $p |- ( ( ph -> ps ) -> ch ) $=
      wph wph wps wi wch wi wph wph wps wi wps wch wph wps pm2.27 ja.2 syl6 wph
      wn wch wph wps wi ja.1 a1d pm2.61i $.
      $( [30-Aug-2004] $) $( [5-Aug-1993] $)
  $}

  ${
    jc.1 $e |- ( ph -> ps ) $.
    jc.2 $e |- ( ph -> ch ) $.
    $( Inference joining the consequents of two premises. $)
    jc $p |- ( ph -> -. ( ps -> -. ch ) ) $=
      wps wch wps wch wn wi wn wph wps wch pm3.2im jc.1 jc.2 sylc $.
      $( [5-Aug-1993] $)
  $}

  $( Simplification.  Similar to Theorem *3.26 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.26im $p |- ( -. ( ph -> -. ps ) -> ph ) $=
    wph wph wps wn wi wph wps wn pm2.21 con1i $.
    $( [5-Aug-1993] $)

  $( Simplification.  Similar to Theorem *3.27 (Simp) of [WhiteheadRussell]
     p. 112. $)
  pm3.27im $p |- ( -. ( ph -> -. ps ) -> ps ) $=
    wps wph wps wn wi wps wn wph ax-1 con1i $.
    $( [5-Aug-1993] $)

  $( Importation theorem expressed with primitive connectives. $)
  impt $p |- ( ( ph -> ( ps -> ch ) ) -> ( -. ( ph -> -. ps ) -> ch ) ) $=
    wph wps wch wi wi wch wph wps wn wi wph wps wch wi wi wph wch wn wps wn wps
    wch wi wch wn wps wn wi wph wps wch con3 imim2i com23 con1d $.
    $( [25-Apr-1994] $)

  $( Exportation theorem expressed with primitive connectives. $)
  expt $p |- ( ( -. ( ph -> -. ps ) -> ch ) -> ( ph -> ( ps -> ch ) ) ) $=
    wph wph wps wn wi wn wch wi wps wch wi wph wps wph wps wn wi wn wch wph wps
    pm3.2im imim1d com12 $.
    $( [5-Aug-1993] $)

  ${
    impi.1 $e |- ( ph -> ( ps -> ch ) ) $.
    $( An importation inference. $)
    impi $p |- ( -. ( ph -> -. ps ) -> ch ) $=
      wph wps wch wi wi wph wps wn wi wn wch wi impi.1 wph wps wch impt ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  ${
    expi.1 $e |- ( -. ( ph -> -. ps ) -> ch ) $.
    $( An exportation inference. $)
    expi $p |- ( ph -> ( ps -> ch ) ) $=
      wph wps wn wi wn wch wi wph wps wch wi wi expi.1 wph wps wch expt ax-mp
      $.
      $( [5-Aug-1993] $)
  $}

  $( Theorem used to justify definition of biconditional ~ def-bi .  (The proof
     was shortened by Josh Purinton, 29-Dec-00.) $)
  bijust $p |- -. ( ( ph -> ph ) -> -. ( ph -> ph ) ) $=
    wph wph wi wph wph wi wn wi wph wph wi wph id wph wph wi pm2.01 mt2 $.
    $( [11-May-1999] $)

