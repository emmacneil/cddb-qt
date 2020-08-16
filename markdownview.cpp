#include "markdownview.h"

MarkdownView::MarkdownView() : QTextEdit()
{
    setReadOnly(true);
    setMarkdown("# Header\n\nplain text\n\n**bold text**");
}
