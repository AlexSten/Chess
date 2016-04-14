#ifndef BOARDSIZES_H
#define BOARDSIZES_H

namespace BoardSizes
{
  const size_t CellSize = 3;
  const size_t BoardWidth = 8;
  const size_t BoardHeight = 8;
  const size_t BorderWidth = 1;
  const size_t CountOfRows = CellSize * BoardHeight + 2 * BorderWidth;
  const size_t RowSize = CellSize * BoardWidth + 2 * BorderWidth;
  const size_t ArraySize = CountOfRows * RowSize;
}
#endif BOARDSIZES_H
