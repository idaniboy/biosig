
% === INDEX  BIOSIG ===
% 
% DOC: Documentation
% ---------------------------------------------
% 	header.txt	specification of header (Dokumentation) 
% 
% 
% demo: [demo's, examples] 
% ---------------------------------------------
% 	demo1		QRS-detection
% 	demo2		estimates and validates BCI classifier
% 	
% 
% T100: [Data Acquistion] 
% ---------------------------------------------
% 
% 
% 
% T200: Data Formats
% ---------------------------------------------
% 	EEGOPEN		opens biosig data and reads header information
% 	EEGREAD		reads biosig data
% 	EEGCLOSE	closes biosig file
% 	EEGWRITE	writes biosig data (currently only BKR, EDF, BDF implemented)
% 	EEGSEEK		set file positon indicator
% 	EEGTELL		returns file position indicator
% 	EEGEOF		checks for end-of-file
% 
% 	LOADEEG 	Opens, reads all data and closes file Biosig files. 
%  	and some utility functions
% 
% 
% T250: Quality Control and Artifact Processing
% ---------------------------------------------
% 	EEG2HIST	calculates histogram
% 	GETTRIGGER	gets trigger points
% 	TRIGG		extract fixed-length trials around trigger points	
% 
% 
% T300: Signal Processing and Feature extraction
% ---------------------------------------------
% 	processing	general framework for blockwise-dataprocessing
% 	getar0		initial AAR parameters
% 	
% 
% T400: Classification, Single Trial Analysis, Statistics,
% ---------------------------------------------
% 	LDBC		linear discriminant analysis
% 	MDBC		mahalanobis distance based classifier
% 	LLBC		log-likelihood based classifier
% 	DECOVM		decomposes an "extended" covariance matrix	
% 	GETCLASSIFIER	estimates classifier from labelled data
% 	FINDCLASSIFIER1	obtains classifier includeding performance test. 
% 	
% 
% T490: Evaluation criteria
% ---------------------------------------------
% 	AUC		area under the curve
% 	ROC		receiver-operator-characteristics 	
% 	MUTINFO		mutual information
% 	QCMAHAL		quality check of multiple discriminator
% 	KAPPA		kappa statistics
% 	BCI3EVAL	Evaluation of BCI results
% 	
% 
% T500: Presentation, Output
% ---------------------------------------------
% 	PLOTA		general plot functions for various data structures
% 
% 
% T550: Topographic Mapping, 3-dimensional display
% ---------------------------------------------
% 
% 
% T600: Interactive Viewer and Scoring  
% ---------------------------------------------
% 	VIEWEDF		EDF-Viewer 


