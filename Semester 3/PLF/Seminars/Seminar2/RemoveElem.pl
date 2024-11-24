% Remove from a list all elements that appear only once
% [1, 2, 1, 4, 1, 3, 4] => [1, 1, 4, 1, 4]

% onlyDup(l1l2..ln, listC) = [], if n = 0
%                       onlyDup(l2..ln, listC), if nrOcc(listC,l1)=1
%                    l1 u onlyDup(l2..ln, listC), if nrOcc(listC,l1)>1

% onlyDupC(l1l2..ln, listC, C) = C, if n = 0
%            = onlyDupC(l2..ln, listC, C), if nrOcc(listC,l1)= 1
%     = onlyDupC(l2..ln, listC, addToEnd(C, l1)), if nrOcc(listC,l1) > 1


