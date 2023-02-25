/**
 * section: Tree
 * synopsis: Navigates a tree to print element names
 * purpose: Parse a file to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and print
 *          all the element name in document order.
 * usage: tree1 filename_or_URL
 * test: tree1 test2.xml > tree1.tmp && diff tree1.tmp $(srcdir)/tree1.res
 * author: Dodji Seketeli
 * copy: see Copyright for the status of this software.
 */
#include <cstdio>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stack>
#ifdef LIBXML_TREE_ENABLED

/*
 *To compile this file using gcc you can type
 *gcc `xml2-config --cflags --libs` -o xmlexample libxml2-example.c
 */

/**
 * print_element_names:
 * @a_node: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
static void PrintElementNames(xmlNode *a_node) {
  xmlNode *cur_node = a_node;
  std::stack<xmlNode *> node_stack; // use a stack to keep track of nodes

  while (!node_stack.empty() || cur_node != nullptr) {
    if (cur_node != nullptr) {
      if (cur_node->type == XML_ELEMENT_NODE) {
        printf("node type: Element, name: %s\n", cur_node->name);
      }

      // push the current node's children onto the stack
      if (cur_node->children != nullptr) {
        node_stack.push(cur_node->children);
      }

      cur_node = cur_node->next;
    } else {
      cur_node = node_stack.top(); // get the next node from the stack
      node_stack.pop();
    }
  }
}

/**
 * Simple example to parse a file called "file.xml",
 * walk down the DOM, and print the name of the
 * xml elements nodes.
 */
auto main(int argc, char **argv) -> int {
  xmlDoc *doc = nullptr;
  xmlNode *root_element = nullptr;

  if (argc != 2) {
    return (1);
  }

  /*
   * this initialize the library and check potential ABI mismatches
   * between the version it was compiled for and the actual shared
   * library used.
   */
  LIBXML_TEST_VERSION

  /*parse the file and get the DOM */
  doc = xmlReadFile(argv[1], nullptr, 0);

  if (doc == NULL) {
    printf("error: could not parse file %s\n", argv[1]);
  }

  /*Get the root element node */
  root_element = xmlDocGetRootElement(doc);

  PrintElementNames(root_element);

  /*free the document */
  xmlFreeDoc(doc);

  /*
   *Free the global variables that may
   *have been allocated by the parser.
   */
  xmlCleanupParser();

  return 0;
}
#else
int main(void) {
  fprintf(stderr, "Tree support not compiled in\n");
  exit(1);
}
#endif