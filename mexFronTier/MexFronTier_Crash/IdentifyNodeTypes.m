function [InsideMask, InteriorMask, BoundaryMask] = IdentifyNodeTypes(PosX, PosY, Front, NumNodesX)

InsideMask  = inpolygon(PosX, PosY, Front.Polygon(:,1), Front.Polygon(:,2));

% InteriorMask = [InsideMask(2:end); InsideMask(1)] &...
%     [InsideMask(end); InsideMask(1:end-1)] &...
%     [InsideMask(NumNodesX+1:end); InsideMask(1:NumNodesX)] &...
%     [InsideMask(end-NumNodesX+1:end); InsideMask(1:end-NumNodesX)];

InteriorMask = [InsideMask(2:end); InsideMask(1)] &...
    [InsideMask(end); InsideMask(1:end-1)] &...
    [InsideMask(NumNodesX+1:end); InsideMask(1:NumNodesX)] &...
    [InsideMask(NumNodesX+2:end); InsideMask(1:NumNodesX+1)] &...
    [InsideMask(NumNodesX:end); InsideMask(1:NumNodesX-1)] &...
    [InsideMask(end-NumNodesX+1:end); InsideMask(1:end-NumNodesX)] &...
    [InsideMask(end-(NumNodesX-1)+1:end); InsideMask(1:end-(NumNodesX-1))] &...
    [InsideMask(end-(NumNodesX+1)+1:end); InsideMask(1:end-(NumNodesX+1))];

BoundaryMask = InsideMask & ~InteriorMask;

