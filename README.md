# From free fermions to limit shapes and beyond.
Lecture notes and code for the course ["From free fermions to limit shapes and beyond"](https://bimsa.net/activity/freefermionslimitshapes/)

Video recordings are available on [Youtube](https://www.youtube.com/playlist?list=PLPPPBj3dto2yTNnA5wTMn1TQTCG2bz8aU) and [BIMSA](https://www.bimsa.cn/newsinfo/838135.html) website. This repository contains lecture notes and demonstration code. 

## Introduction:

This course is dedicated to the thorough introduction of the subjects,
mentioned in my talk at [the BIMSA Integrable Systems Seminar](https://researchseminars.org/talk/BIMSA-ISS/1/)

In this course we will start from the infinite-wedge formalism and
boson-fermion correspondence, as described in the Chapter 14 of Victor
Kac's book "Infinite dimensional Lie algebras". We will use this
formalism to derive the limit shape for Young diagrams for the
Plancherel measure, as was done in the works of Andrei Okounkov. Then we
will consider the measures on the diagrams related to the skew Howe
duality. After studying GL(n)-GL(k) skew Howe duality we will consider
other classical series of Lie groups. Connections to the determinantal
point processes, orthogonal polynomials, Riemann-Hilbert problem and
integrable systems will be discussed.

## Audience:
  Graduate, Undergraduate

## Prerequisite

The knowledge of linear algebra and basic methods of analysis (integral
calculus, theory of the function of a complex variable) is required.
Some knowledge of Quantum Mechanics and Statistical Mechanics would be
useful. The knowledge of representation theory of the symmetric group
and Lie groups would be useful. 

## References:
1. Kac V.G. - Infinite dimensional Lie algebras-CUP (1995)
2. Okounkov, Andrei. "Infinite wedge and random partitions." Selecta
Mathematica 7.1 (2001): 57.
3. Okounkov, Andrei. "Symmetric functions and random partitions."
Symmetric functions 2001: surveys of developments and perspectives.
Springer Netherlands, 2002.
4. Borodin, Alexei, and Vadim Gorin. "Lectures on integrable
probability." Probability and statistical physics in St. Petersburg 91
(2016): 155-214.
5. Proctor, Robert A. "Reflection and algorithm proofs of some more Lie
group dual pair identities." Journal of Combinatorial Theory, Series A
62.1 (1993): 107-127.
6. Nazarov, A., P. Nikitin, and D. Sarafannikov. "Skew Howe duality and
q-Krawtchouk polynomial ensemble." Representation theory, dynamical
systems, combinatorial methods. Part XXXIV, Zap. Nauchn. Sem. POMI 517:
106-124.
7. Betea, Dan, Anton Nazarov, and Travis Scrimshaw. "Limit shapes for
skew Howe duality." arXiv preprint arXiv:2211.13728 (2022). 
8. Bleher, P.M., 2011. Lectures on random matrix models: the
Riemann–Hilbert approach. In Random Matrices, Random Processes and
Integrable Systems (pp. 251-349). New York, NY: Springer New York.

## Syllabus:

1. Infinite wedge representation
2. Free fermions and bosonization
3. Vertex operators
4. Partitions and Schur polynomials
5. Boson-fermion correspondence
6. Plancherel measure on partitions
7. Correlation kernel from free fermions and limit shape for Plancherel measure
8. Relation of Plancherel measure to RSK algorithm
9. RSK and Schur-Weyl duality between GL(n) and S_k
10. Representations of GL(n), exterior powers and exterior algebra
11. Skew Howe GL(n)−GL(k) duality
12. Probability measure on Young diagrams in the box and dual RSK algorithm
13. Limit shape for skew GL(n)−GL(k) duality from free fermions
14. Local asymptotics of correlation kernel for skew GL(n)−GL(k) duality, Airy kernel, local fluctuations around limit shape
15. Connection to lozenge tilings and to five-vertex model
16. Skew Howe dualities for other classical series of Lie groups
17. Young diagrams and tableaux for symplectic groups
18. Proctor algorithm for skew Howe duality of symplectic groups Sp(2n) and Sp(2k)
19. Limit shapes for symplectic groups and scalar Riemann-Hilbert problem
20. Global fluctuations around limit shape, Krawtchouk and q-Krawtchouk orthogonal polynomials, Central limit theorem
21. Asymptotics of orthogonal polynomials, Riemann-Hilbert problem and its integrability


## Lecturer Intro:
Anton Nazarov is an associate professor at Saint Petersburg State
University, Russia. He completed his PhD at the department of high-energy and
elementary particle physics of Saint Petersburg State University in
2012 under the supervision of Vladimir Lyakhovsky. In 2013-2014 he was a
postdoc at the University of Chicago. Anton's research interests are
representation theory of Lie algebras, conformal field theory,
integrable systems, determinantal point processes. 

## About lecture notes and demonstrations

Lecture notes are handwritten using Wacom tablet and [Xournal++](https://xournalpp.github.io/). Source Xournal++ files for lecture notes are available in this repository as well as PDF files of lecture notes. 

On some lectures computer demonstrations were used. Most code in demonstrations is written in Python, but most of the times [Sage](sagemath.org) is used for simplicity of interaction with C code. To run these demonstrations on Linux it is enough to install Sage and development libraries from the distribution repository (e.g. `apt install sage libgmp-dev`). Faster implementations of [dual RSK algorithm](dual-rsk-for-sage.c) and [Proctor algorithm for simplectic groups](proctor.c) are written in C and available in this repository. 

## List of lectures

1. Course overview, hook walk algorithm: [Lecture notes](Lecture1.pdf), [Jupyter notebook](Lecture1.ipynb), [Video](https://youtu.be/CQsAI9FybfA)
2. Infinite wedge space, Heisenberg algebra, bosonic Fock space, free fermions: [Lecture notes](Lecture2-2023-05-19-Note-07-21.pdf), [Video](https://youtu.be/vfInsBqF_Bo)
3. Fermionic Fock space, Schur polynomials, vertex operators: [Lecture notes](Lecture3-2023-05-26-Note-07-22.pdf), [Video](https://youtu.be/fpIU_quseSI)
4. Integral representation for the correlation kernel from the matrix element of vertex operators: [Lecture notes](Lecture4-2023-05-31-Note-07-14.pdf), [Video](https://youtu.be/gCbiRpwj9JU)
5. Asymptotic analysis of the correlation kernel and limit shape for the Poissonized Plancherel measure: [Lecture notes](Lecture5-2023-06-02-Note-07-17.pdf), [Jupyter notebook](Lecture5.ipynb), [Video](https://youtu.be/HbD2P1z8j9w)
6. Representation theory of general linear group, Young diagrams, Young tableaux, Sylevester's lemma: [Lecture notes](Lecture6-2023-06-07-Note-07-17.pdf), [Video](https://youtu.be/HbD2P1z8j9w)
7. Construction of the irreducible representations of general linear group. Characters and Schur polynomials: [Lecture notes](Lecture7-2023-06-09-Note-07-12.pdf), [Video](https://youtu.be/JVNeFmWpkPg)
8. Semistandard Young tableaux, Gelfand-Tsetlin patterns and lozenge tilings. Schur-Weyl duality and Robinson-Schensted-Knuth algorithm: [Lecture notes](Lecture8-2023-06-14-Note-05-12.pdf), [Jupyter notebook](Lecture8.ipynb), [Video](https://youtu.be/dksC_1_HnxY)
9. Limit shape for Poissonized Schur-Weyl measure from free fermions, Biane's plot with a different normalization: [Lecture notes](Lecture9-2023-06-21-Note-07-17.pdf), [Jupyter notebook](Lecture9.ipynb), [Video](https://youtu.be/sPAVBs0moaE)
10. Limit shape for skew Howe GL(n)xGL(k) duality: [Lecture notes](Lecture10-2023-06-23-Note-07-14.pdf), [Jupyter notebook](Lecture10.ipynb), [Video](https://youtu.be/YVJ7hDcolQk)
11. Skew Howe duality, limit shapes for the constant, exponential and generic specializations: [Lecture notes](Lecture11-2023-06-28-Note-07-16.pdf), [Video](https://youtu.be/1a1PTdWmaV4)
12. Fluctuations of the first row of random Young diagram, Tracy-Widom distribution and Airy kernel: [Lecture notes](Lecture12-2023-06-30-Note-07-17.pdf), [Jupyter notebook](Lecture12.ipynb), [Video](https://youtu.be/_agj-AXAe2s)
13. Fluctuations of the first row in the corner, discrete "critical" distribution of Gravner, Tracy and Widom: [Lecture notes](Lecture13-2023-07-05-Note-05-37.pdf), [Jupyter notebook](Lecture13.ipynb), [Video](https://youtu.be/TLtb_W27O2o)
14. Fluctuations near the corner in skew GL(n)xGL(k) case and discrete Hermite kernel: [Lecture notes](Lecture14-2023-07-07-Note-07-13.pdf), [Jupyter notebook](Lecture14.ipynb), [Video](https://youtu.be/uqXJTK8jh1M)
15. Skew GL(n)xGL(k) Howe duality, lozenge tilings of a hexagon glued from two parts, domino tilings of Aztec diamond, relation to five-vertex model: [Lecture notes](Lecture15-2023-07-12-Note-05-20.pdf), [Jupyter notebook](Lecture15.ipynb), [Video](https://youtu.be/IHPY794Icu0)
16. Orthogonal and symplectic Lie groups, symplectic Schur polynomials, King tableaux, Berele insertion, Proctor's algorithm for skew Sp(2n)xSp(2k) Howe duality: [Lecture notes](Lecture16-2023-07-14-Note-05-31.pdf), [Jupyter notebook](Lecture16.ipynb), [Video](https://youtu.be/tdmd2CKQZNQ)
17. Vertex operators for symplectic characters, correlation kernel for Sp x GL - duality: [Lecture notes](Lecture17-2023-08-09-Note-07-20.pdf), [Video](https://youtu.be/z_oSA9YV-Sc)
18. Limit shape and fluctuations in Sp x GL duality, Airy 2-to-1 kernel: [Lecture notes](Lecture18-2023-08-11-Note-07-22.pdf), [Video](https://youtu.be/TyudrdbE8_I)
19. Difficulties with vertex construction for Sp x Sp skew Howe duality, combinatorial derivation of dimension formula for complement conjugate Young diagram, variational problem for limit shape: [Lecture notes](Lecture19-2023-08-16-Note-07-16.pdf), [Video](https://youtu.be/Na4jC_6ZPrk)
20. Solution of variational problem for the limit shape in skew Sp(2n)xSp(2k) Howe duality, proof of the uniform convergence of Young diagrams to the limit shape: [Lecture notes](Lecture20-2023-08-18-Note-07-12.pdf), [Video](https://youtu.be/yxn-hdVtOxg)
21. From double contour integral representation for the correlation kernel in GL(n)xGL(k) duality to Krawtchouk polynomials: [Lecture notes](Lecture21-2023-08-23-Note-07-18.pdf), [Video](https://youtu.be/QQf6fOJKTX8)
22. Christoffel-Darboux kernel, orthogonal polynomial ensembles, derivation of the limit shape using second order difference equation for Krawtchouk ensemble, three-term recurrence relation and central limit theorem for global fluctuations: [Lecture notes](Lecture22-2023-08-25-Note-07-23.pdf), [Jupyter notebook](Lecture22.ipynb), [Video](https://youtu.be/j7UjSDePLVo)
23. Riemann-Hilbert approach to orthogonal polynomials, Lax pair, discrete Painleve equation. First part of asymptotic analysis for orthogonal polynomials: transformations of Riemann-Hilbert problem and global parametrix: [Lecture notes](Lecture23-2023-08-30-Note-07-14.pdf), [Video](https://youtu.be/Dq6MyamahIE)
24. Second part of asymptotic analysis of orthogonal polynomial by Riemann-Hilbert approach: local parametrices, Airy functions. Asymptotics of the recurrence coefficients: [Lecture notes](Lecture24-2023-09-01-Note-07-14.pdf), [Video](https://youtu.be/jgfEVV27wac)
