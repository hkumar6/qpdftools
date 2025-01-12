#include "pdfUtils.hpp"

// Definition of the function
int getPdfPageCount(const QString &filePath) {
  QPdfDocument pdfDocument;
  if (pdfDocument.load(filePath) == QPdfDocument::Error::None) {
    return pdfDocument.pageCount();
  } else {
    // Print an error message if the PDF couldn't be loaded
    // from the point where the function was called
    return 0; // Return 0 if the PDF couldn't be loaded
  }
}