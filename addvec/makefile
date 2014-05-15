PROJECT = addvec

BINARY = $(PROJECT).bin

SOURCES = addvec.c

HEADERS = addvec.h

DEADSOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)
DEADOBJECTS = $(DEADSOURCES:.c=.do)

DOCSRC = instructions.tex
DOCS = $(DOCSRC:.tex=.pdf)

CFLAGS = -Wall -pg
LDFLAGS = -Wall -pg

all: $(BINARY) $(DOCS)
	@echo Testing...
	@date +%s >> data.txt
	@echo ======================================== BEGIN APPLICATION OUTPUT | tee -a data.txt
	@echo | tee -a data.txt
	@./$(BINARY) | tee -a data.txt
	@echo | tee -a data.txt
	@echo ========================================== END APPLICATION OUTPUT | tee -a data.txt
	@echo addvec.c: >> data.txt
	@cat addvec.c >> data.txt

$(BINARY): $(OBJECTS) $(DEADOBJECTS)
	@echo Linking $(BINARY)...
	@gcc $(LDFLAGS) $(OBJECTS) $(DEADOBJECTS) -o $(BINARY)

%.o: %.c
	@echo Building $@...
	@gcc $< -c $(CFLAGS) -o $@

%.do: %.c
	@echo Building $@...
	@gcc $< -c $(CFLAGS) -o $@

%.pdf: %.tex
	@echo Building documentation $@...
	@pdflatex -interaction=batchmode $<
	@rm *.log *.aux

clean:
	@rm -f *.o *.bin
	@rm -rf dist
	@rm -f $(PROJECT).zip
	@rm -f *.log *.aux
	@rm -f gmon.out

fullclean: clean
	@rm -f *.do
	@rm -f *.pdf
	@rm -f data.txt

dist: $(DOCS) $(DEADOBJECTS) $(SOURCES) $(HEADERS)
	@rm -rf dist
	@mkdir dist
	@cp makefile dist/
	@cp $(SOURCES) dist/
	@cp $(HEADERS) dist/
	@cp $(DEADOBJECTS) dist/
	@cp *.pdf dist/
	@zip -r $(PROJECT).zip dist/
	@cp $(DOCS) dist/

