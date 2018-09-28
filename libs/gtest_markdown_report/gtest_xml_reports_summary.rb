require "fileutils"
require "optparse"
require "rexml/document"

# NilClass extensions
class NilClass
  def nilOrEmpty?
    true
  end
end

# String extensions
class String
  def unixPath()
    self.gsub('\\', '/')
  end
  def windowsPath()
    self.gsub('/', '\\')
  end
  def startsWith?(start)
    return (self[0...(start.length)] == start)
  end
  def endsWith?(ends)
    return (self[(-ends.length)..-1] == ends)
  end
  def nilOrEmpty?
	return (self.to_s.strip.length == 0)
  end
end

# Globals
cmd_dir = Dir.pwd.unixPath

# Report errors and exit
def exit_on_error(message)
	puts message
	puts "Aborting... you have to restore your repository with 'git revert'"
	exit
end

# Report missing option and exit
def exit_on_missing_option(message)
	puts message
	puts "Use -h for help."
	puts "Aborting..."
	exit
end

# Check input
def check_input(input)
	if(!File.directory?(input))
		exit_on_error("ERROR! check_input: Cannot find input. Directory '" + input + "' is missing.")
	end
end

# Copy header to markdown report
def copy_header_to_markdown_report(md_file, template)
	if(File.file?(template))
		File.readlines(template).each do |line|
            md_file.puts(line)
        end
	end
end

# Generate markdown report
def generate_markdown_report(xml_source_directory_name, md_file)
    reports = 0
    testsuites = 0
    testcases = 0
    errors = 0
    failures = 0
    disabled = 0
    Dir.glob(xml_source_directory_name + "/**/*_tests_report.xml") do |xml_source_filename|
        xml_report = File.open(xml_source_filename) { |xml_file| REXML::Document.new(xml_file) }
        reports += 1
        xml_testsuites = REXML::XPath.first(xml_report, "/testsuites")
        xml_testsuites.elements.each("testsuite") do |xml_testsuite|
            testsuites += 1
        end
        testcases += xml_testsuites.attributes["tests"].to_i
        errors += xml_testsuites.attributes["errors"].to_i
        failures += xml_testsuites.attributes["failures"].to_i
        disabled += xml_testsuites.attributes["disabled"].to_i
    end
    md_file.puts("")
    md_file.puts("# Summary")
    md_file.puts("")
    md_file.puts("* " + reports.to_s + " unit test applications executed, " + (reports/9).to_s + " for each toolset" )
    md_file.puts("* " + testsuites.to_s + " unit test suites, on average " + (testsuites/9).to_s + " for each toolset")
    md_file.puts("* " + testcases.to_s + " unit test cases, on average " + (testcases/9).to_s + " for each toolset")
    md_file.puts("* " + errors.to_s + " errors")
    md_file.puts("* " + failures.to_s + " failures")
    md_file.puts("* " + disabled.to_s + " disabled test cases")
end

# Check options
options = {}
OptionParser.new do |opts|
	opts.banner = "Usage: gtest_xml_reports_summary.rb [options]"
	opts.on("-i", "--input INPUT", "Mandatory: Input directory, e.g. ~/build") { |v| options[:input] = v.unixPath }
	opts.on("-o", "--output OUTPUT", "Mandatory: Output file name, e.g. report.md") { |v| options[:output] = v.unixPath }
	opts.on("-t", "--template TEMPLATE", "Mandatory: Header template for the markdown report, e.g. report_header.md") { |v| options[:template] = v }
	opts.on("-h", "--help", "Show this help message.") { puts opts; exit }
end.parse!
if options[:input] == nil
	exit_on_missing_option("Input directory must be given.")
end
if options[:output] == nil
	exit_on_missing_option("Output file name must be given.")
end
if options[:template] == nil
	exit_on_missing_option("Template file name must be given.")
end

# Check input
xml_source_directory_name = options[:input].to_s.unixPath
check_input(xml_source_directory_name)

# Create markdown report
md_filename = options[:output].to_s.unixPath
md_file = File.open(md_filename, "w+")

# Copy header to markdown report
md_template_filename = options[:template].to_s.unixPath
copy_header_to_markdown_report(md_file, md_template_filename)

# Generate markdown report
generate_markdown_report(xml_source_directory_name, md_file)
