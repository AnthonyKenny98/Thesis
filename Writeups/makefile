TEX_COMMAND = pdflatex
BIB_COMMAND = bibtex

TEX_FILES = $(wildcard **/*.tex)
BIB_FILES = $(wildcard **/*.bib)

OUTPUT_DIRECTORIES = $(addsuffix output/,$(wildcard */))
PDF_FILES = $(join $(dir $(TEX_FILES)),$(addprefix output/,$(notdir $(TEX_FILES:tex=pdf))))

all: mkdir $(PDF_FILES)

mkdir:
	@mkdir -p $(OUTPUT_DIRECTORIES)

$(PDF_FILES): $(TEX_FILES)
	@$(TEX_COMMAND) -file-line-error -halt-on-error -output-directory $(dir $@) -aux_directory=$(dir $@) $(subst output/,$(notdir $(@:pdf=tex)),$(dir $@))
	@$(TEX_COMMAND) -file-line-error -halt-on-error -output-directory $(dir $@) -aux_directory=$(dir $@) $(subst output/,$(notdir $(@:pdf=tex)),$(dir $@))

clean:
	@rm -rf $(OUTPUT_DIRECTORIES)